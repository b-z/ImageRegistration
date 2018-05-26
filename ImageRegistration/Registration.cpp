#include "stdafx.h"
#include "Registration.h"
#include "RegistrationThread.h"
#include <iostream>
#include <cmath>

double random(double LO, double HI) {
    return LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
}

Registration::Registration(RegistrationThread* thr, cv::Mat ref, cv::Mat tar, TransformType t, SimilarityType s, OptimizationType o) {
    srand(time(0));
    thread = thr;
    ref_ori_img = ref;
    tar_ori_img = tar;
    cv::resize(ref, ref_img, cv::Size(0, 0), SCALE, SCALE);
    cv::resize(tar, tar_img, cv::Size(0, 0), SCALE, SCALE);

    trans_img = cv::Mat(tar_img.rows, tar_img.cols, tar_img.type());
    trans_ori_img = cv::Mat(tar_ori_img.rows, tar_ori_img.cols, tar_ori_img.type());
    transform_type = t;
    transform = cv::Mat(2, 3, CV_32FC1);
    border_value = cv::mean(tar_img); // cv::Scalar(0, 0, 0);
    similarity_type = s;
    optimization_type = o;
    //limits.resize(6);
}


Registration::~Registration()
{
}

void Registration::runRegistration() {
    initialize();
    switch (optimization_type) {
    case OPTIMIZE_NAIVE:
        optimizeNaive();
        break;
    case OPTIMIZE_GD:
        optimizeGD();
        break;
    }
    std::cout << "finished!" << std::endl;
}

void Registration::initialize() {
    loss = 1e30;
    iter = 0;
    int c = trans_img.cols;
    int r = trans_img.rows;
    switch (transform_type) {
    case TRANSFORM_TRANSLATE:
        params.resize(2); // tx ty
        limits.resize(2);
        steps.resize(2);
        limits[0] = std::make_pair(-c / 2, c / 2);
        limits[1] = std::make_pair(-r / 2, r / 2);
        for (int i = 0; i < params.size(); i++) {
            params[i] = limits[i].first;
        }
        transform.at<float>(0, 0) = 1;
        transform.at<float>(0, 1) = 0;
        transform.at<float>(1, 0) = 0;
        transform.at<float>(1, 1) = 1;
        steps[0] = 1;
        steps[1] = 1;
        break;
    case TRANSFORM_ROTATE:
        params.resize(4); // cx cy angle scale
        limits.resize(4);
        steps.resize(4);
        limits[0] = std::make_pair(-c / 2, c / 2);
        limits[1] = std::make_pair(-r / 2, r / 2);
        limits[2] = std::make_pair(-180, 180);
        limits[3] = std::make_pair(0.5, 2);
        for (int i = 0; i < params.size(); i++) {
            params[i] = limits[i].first;
        }
        steps[0] = 1;
        steps[1] = 1;
        steps[2] = 1;
        steps[3] = 0.01;
        break;
    case TRANSFORM_AFFINE:
        params.resize(6);
        limits.resize(6);
        steps.resize(6);
        limits[0] = std::make_pair(-c / 2, c / 2);
        limits[1] = std::make_pair(-r / 2, r / 2); // top left
        limits[2] = std::make_pair(c / 2, c * 3 / 2);
        limits[3] = std::make_pair(-r / 2, r / 2); // top right
        limits[4] = std::make_pair(-c / 2, c / 2);
        limits[5] = std::make_pair(r / 2, r * 3 / 2); // bottom left

        for (int i = 0; i < params.size(); i++) {
            params[i] = limits[i].first;
        }
        for (int i = 0; i < params.size(); i++) {
            steps[i] = 1;
        }
        break;
    case TRANSFORM_PERSPECTIVE:
        params.resize(8);
        limits.resize(8);
        steps.resize(8);
        limits[0] = std::make_pair(-c / 2, c / 2);
        limits[1] = std::make_pair(-r / 2, r / 2); // top left
        limits[2] = std::make_pair(c / 2, c * 3 / 2);
        limits[3] = std::make_pair(-r / 2, r / 2); // top right
        limits[4] = std::make_pair(-c / 2, c / 2);
        limits[5] = std::make_pair(r / 2, r * 3 / 2); // bottom left
        limits[6] = std::make_pair(c / 2, c * 3 / 2);
        limits[7] = std::make_pair(r / 2, r * 3 / 2); // bottom right

        for (int i = 0; i < params.size(); i++) {
            params[i] = limits[i].first;
        }
        for (int i = 0; i < params.size(); i++) {
            steps[i] = 1;
        }
        break;
    }
}

void Registration::completeIteration() {
    // one iteration
    applyTransform();
    double s = getSimilarity(trans_img, tar_img, similarity_type);
    if (s < loss) {
        loss = s;
        showTransformedImage();
        std::cout << "iter: " << iter
            << "\tloss: " << loss;
        for (auto & p : params) std::cout << "\t" << p;
        std::cout << std::endl;
    }
    if (loss == s || iter % 1000 == 0) {
        thread->addDataPoint(iter, s, loss);
    }
    iter++;
}

void Registration::optimizeNaive() {
    optimizeNaiveHelper(0);
}

void Registration::optimizeNaiveHelper(int pos) {
    if (pos >= params.size()) {
        completeIteration();
        return;
    }
    for (float i = limits[pos].first; i <= limits[pos].second; i += steps[pos]) {
        params[pos] = i;
        optimizeNaiveHelper(pos + 1);
    }
}

void Registration::optimizeGD() {
    //std::vector<float> global_best = params;
    for (int i = 0; i < 10000; i++) {
        double tmp_loss = 1e30;
        double cur_loss = 1e30;

        for (int i = 0; i < params.size(); i++) {
            // give random start values
            params[i] = random(limits[i].first, limits[i].second);
        }

        while (true) {
            std::vector<float> old = params;
            std::vector<float> best = params;
            for (int pos = 0; pos < params.size(); pos++) {
                params[pos] = old[pos] + steps[pos];
                optimizeGDHelper(best, cur_loss);
                params[pos] = old[pos] - steps[pos];
                optimizeGDHelper(best, cur_loss);
                params[pos] = old[pos];
            }
            //optimizeGDHelper(old, best, cur_loss, 0);
            if (tmp_loss == cur_loss) break;
            tmp_loss = cur_loss;
            params = best;
            completeIteration();
        }
    }
}

void Registration::optimizeGDHelper(std::vector<float>& best, double& cur_loss) {
    applyTransform();
    double s = getSimilarity(trans_img, tar_img, similarity_type);
    if (s < cur_loss) {
        cur_loss = s;
        best = params;
    }
}


double Registration::getSimilarity(cv::Mat img1, cv::Mat img2, SimilarityType s) {
    double similarity = 0;
    double npixel = img1.rows * img1.cols;
    switch (s) {
    case SIMILARITY_L1:
        similarity = cv::norm(img1, img2, cv::NORM_L1);
        similarity /= npixel;
        break;
    case SIMILARITY_L2:
        similarity = cv::norm(img1, img2, cv::NORM_L2);
        similarity /= npixel;
        break;
    case SIMILARITY_LINF:
        similarity = cv::norm(img1, img2, cv::NORM_INF);
        similarity /= npixel;
        break;
    }
    return similarity;
}

void Registration::applyTransform(bool original_image) {
    cv::Point2f src[3] = { cv::Point2f(0, 0), cv::Point2f(tar_img.cols, 0), cv::Point2f(0, tar_img.rows) };
    cv::Point2f dst[3];
    cv::Point2f src_[4] = { cv::Point2f(0, 0), cv::Point2f(tar_img.cols, 0), cv::Point2f(0, tar_img.rows), cv::Point2f(tar_img.cols, tar_img.rows) };
    cv::Point2f dst_[4];

    switch (transform_type) {
    case TRANSFORM_TRANSLATE:
        transform.at<float>(0, 2) = params[0];
        transform.at<float>(1, 2) = params[1];
        break;
    case TRANSFORM_ROTATE:
        transform = cv::getRotationMatrix2D(cv::Point2f(0, 0), params[2], params[3]);
        transform.at<float>(0, 2) = params[0];
        transform.at<float>(1, 2) = params[1];
        break;
    case TRANSFORM_AFFINE:        
        for (int i = 0; i < 6; i += 2) dst[i / 2] = cv::Point2f(params[i], params[i + 1]);
        transform = cv::getAffineTransform(src, dst);
        //std::cout << transform.at<float>(0, 2) << std::endl;
        break;
    case TRANSFORM_PERSPECTIVE:
        for (int i = 0; i < 8; i += 2) dst_[i / 2] = cv::Point2f(params[i], params[i + 1]);
        transform = cv::getPerspectiveTransform(src_, dst_);
        //std::cout << transform.at<float>(0, 2) << std::endl;
        break;
    }
    if (transform_type == TRANSFORM_PERSPECTIVE) {
        cv::warpPerspective(ref_img, trans_img, transform, trans_img.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, border_value);
    } else {
        if (original_image) {
            cv::Mat t = transform.clone();
            t.at<float>(0, 2) /= SCALE;
            t.at<float>(1, 2) /= SCALE;
            cv::warpAffine(ref_ori_img, trans_ori_img, t, trans_ori_img.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, border_value);
        } else {
            cv::warpAffine(ref_img, trans_img, transform, trans_img.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, border_value);
        }
    }
}

void Registration::showTransformedImage() {
    applyTransform();
    cv::Mat* img = new cv::Mat;
    *img = trans_img.clone();
    thread->showTransformedImage(img);
    Sleep(50);
    //applyTransform(true);
    //cv::Mat* img = new cv::Mat;
    //*img = trans_ori_img.clone();
    //thread->showTransformedImage(img);
    //Sleep(50);
}
