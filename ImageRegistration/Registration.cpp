#include "stdafx.h"
#include "Registration.h"
#include "RegistrationThread.h"
#include <iostream>
#include <cmath>

double random(double LO, double HI) {
    return LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
}

Registration::Registration(RegistrationThread* thr, cv::Mat ref, cv::Mat tar, TransformType t, SimilarityType s, OptimizationType o) {
    srand(time(NULL));
    thread = thr;
    ref_ori_img = ref;
    tar_ori_img = tar;
    cv::resize(ref, ref_img, cv::Size(0, 0), SCALE, SCALE);
    cv::resize(tar, tar_img, cv::Size(0, 0), SCALE, SCALE);

    trans_img = cv::Mat(tar_img.rows, tar_img.cols, tar_img.type());
    trans_ori_img = cv::Mat(tar_ori_img.rows, tar_ori_img.cols, tar_ori_img.type());
    transform_type = t;
    transform = cv::Mat(2, 3, CV_32FC1);
    transform_ = cv::Mat(2, 3, CV_32FC1);
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
    case OPTIMIZE_SA:
        optimizeSA();
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
        transform_.at<float>(0, 0) = 1;
        transform_.at<float>(0, 1) = 0;
        transform_.at<float>(1, 0) = 0;
        transform_.at<float>(1, 1) = 1;
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

void Registration::completeIteration(bool update) {
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
    if (loss == s || update) {
        thread->addDataPoint(iter, s, loss);
    }
    iter++;
}

void Registration::optimizeNaive() {
    optimizeNaiveHelper(0);
}

void Registration::optimizeNaiveHelper(int pos) {
    if (pos >= params.size()) {
        completeIteration(iter % 20 == 0);
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

        for (int j = 0; j < params.size(); j++) {
            // give random start values
            params[j] = random(limits[j].first, limits[j].second);
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
            if (tmp_loss == cur_loss) {
                break;
            }
            tmp_loss = cur_loss;
            params = best;
            completeIteration(iter % 50 == 0);
        }
        completeIteration(true);
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

void Registration::optimizeSA() {
    for (int i = 0; i < 10000; i++) {
        for (int j = 0; j < params.size(); j++) {
            // give random start values
            params[j] = random(limits[j].first, limits[j].second);
        }
        applyTransform();
        double fi = getSimilarity(trans_img, tar_img, similarity_type);
        double temp = 10;
        double r = 0.99;
        int k = 1000;
        while (k > 0) {
            // select a random neighbor
            int len = params.size();
            int r1 = rand() % len;
            double r2 = random(1, 10) * ((rand() % 2) * 2 - 1);
            params[r1] += r2 * steps[r1];
            applyTransform();
            double fj = getSimilarity(trans_img, tar_img, similarity_type);
            double delta = fj - fi;
            if (random(0, 1) < exp(-delta / temp)) {
                // jump to this neighbor
                completeIteration(iter % 20 == 0);
                fi = fj;
            }
            else {
                iter++;
                params[r1] -= r2 * steps[r1];
            }
            temp *= r;
            k--;
        }
        completeIteration(true);
        thread->addDataPoint(iter + 1, 2, loss);
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
    cv::Point2f src_[3] = { cv::Point2f(0, 0), cv::Point2f(tar_ori_img.cols, 0), cv::Point2f(0, tar_ori_img.rows) };
    cv::Point2f dst[3];
    cv::Point2f dst_[3];
    cv::Point2f srcp[4] = { cv::Point2f(0, 0), cv::Point2f(tar_img.cols, 0), cv::Point2f(0, tar_img.rows), cv::Point2f(tar_img.cols, tar_img.rows) };
    cv::Point2f srcp_[4] = { cv::Point2f(0, 0), cv::Point2f(tar_ori_img.cols, 0), cv::Point2f(0, tar_ori_img.rows), cv::Point2f(tar_ori_img.cols, tar_ori_img.rows) };
    cv::Point2f dstp[4];
    cv::Point2f dstp_[4];

    switch (transform_type) {
    case TRANSFORM_TRANSLATE:
        transform.at<float>(0, 2) = params[0];
        transform.at<float>(1, 2) = params[1];
        transform_.at<float>(0, 2) = params[0] / SCALE;
        transform_.at<float>(1, 2) = params[1] / SCALE;
        break;
    case TRANSFORM_ROTATE:
        transform = cv::getRotationMatrix2D(cv::Point2f(params[0], params[1]), params[2], params[3]);
        transform_ = cv::getRotationMatrix2D(cv::Point2f(params[0] / SCALE, params[1] / SCALE), params[2], params[3]);
        break;
    case TRANSFORM_AFFINE:        
        for (int i = 0; i < 6; i += 2) dst[i / 2] = cv::Point2f(params[i], params[i + 1]);
        for (int i = 0; i < 6; i += 2) dst_[i / 2] = cv::Point2f(params[i] / SCALE, params[i + 1] / SCALE);
        transform = cv::getAffineTransform(src, dst);
        transform_ = cv::getAffineTransform(src_, dst_);
        break;
    case TRANSFORM_PERSPECTIVE:
        for (int i = 0; i < 8; i += 2) dstp[i / 2] = cv::Point2f(params[i], params[i + 1]);
        for (int i = 0; i < 8; i += 2) dstp_[i / 2] = cv::Point2f(params[i] / SCALE, params[i + 1] / SCALE);
        transform = cv::getPerspectiveTransform(srcp, dstp);
        transform_ = cv::getPerspectiveTransform(srcp_, dstp_);
        break;
    }
    if (transform_type == TRANSFORM_PERSPECTIVE) {
        if (original_image) {
            cv::warpPerspective(ref_ori_img, trans_ori_img, transform_, trans_ori_img.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, border_value);
        } else {
            cv::warpPerspective(ref_img, trans_img, transform, trans_img.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, border_value);
        }        
    } else {
        if (original_image) {
            cv::warpAffine(ref_ori_img, trans_ori_img, transform_, trans_ori_img.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, border_value);
        } else {
            cv::warpAffine(ref_img, trans_img, transform, trans_img.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, border_value);
        }
    }
}

void Registration::showTransformedImage() {
    applyTransform(true);
    cv::Mat* img = new cv::Mat;
    *img = trans_ori_img.clone();
    thread->showTransformedImage(img);
}
