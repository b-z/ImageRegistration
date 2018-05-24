#include "stdafx.h"
#include "Registration.h"
#include "RegistrationThread.h"
#include <iostream>
#include <cmath>

Registration::Registration(RegistrationThread* thr, cv::Mat ref, cv::Mat tar, TransformType t, SimilarityType s, OptimizationType o) {
    thread = thr;
    ref_ori_img = ref;
    tar_ori_img = tar;
    cv::resize(ref, ref_img, cv::Size(0, 0), 0.1, 0.1);
    cv::resize(tar, tar_img, cv::Size(0, 0), 0.1, 0.1);

    trans_img = cv::Mat(tar_img.rows, tar_img.cols, tar_img.type());
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
        limits[0] = std::make_pair(-c, c);
        limits[1] = std::make_pair(-r, r);
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
        limits[0] = std::make_pair(0, c);
        limits[1] = std::make_pair(0, r);
        limits[2] = std::make_pair(0, 360);
        limits[3] = std::make_pair(0.5, 2);
        for (int i = 0; i < params.size(); i++) {
            params[i] = limits[i].first;
        }
        steps[0] = 4;
        steps[1] = 4;
        steps[2] = 4;
        steps[3] = 0.04;
        break;
    }
}

void Registration::optimizeNaive() {
    optimizeNaiveHelper(0);
}

void Registration::optimizeNaiveHelper(int pos) {
    if (pos >= params.size()) {
        // one iteration
        applyTransform();
        double s = getSimilarity(trans_img, tar_img, SIMILARITY_L2);
        if (s < loss) {
            loss = s;
            showCombinedImage();
            std::cout << "iter: " << iter
                << "\tloss: " << loss;
            for (auto & p : params)std::cout << "\t" << p;
            std::cout << std::endl;
        }
        iter++;
        return;
    }
    for (float i = limits[pos].first; i <= limits[pos].second; i += steps[pos]) {
        params[pos] = i;
        optimizeNaiveHelper(pos + 1);
    }
}

double Registration::getSimilarity(cv::Mat img1, cv::Mat img2, SimilarityType s) {
    double similarity = 0;
    double npixel = img1.rows * img1.cols;
    switch (s) {
    case SIMILARITY_L1:
        similarity = cv::norm(img1, img2, CV_L1);
        similarity /= npixel;
        break;
    case SIMILARITY_L2:
        similarity = cv::norm(img1, img2, CV_L2);
        similarity /= npixel;
        break;
    }
    return similarity;
}

void Registration::applyTransform() {
    switch (transform_type) {
    case TRANSFORM_TRANSLATE:
        transform.at<float>(0, 2) = params[0];
        transform.at<float>(1, 2) = params[1];
        cv::warpAffine(ref_img, trans_img, transform, trans_img.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, border_value);
        break;
    case TRANSFORM_ROTATE:
        transform = cv::getRotationMatrix2D(cv::Point2f(params[0], params[1]), params[2], params[3]);
        cv::warpAffine(ref_img, trans_img, transform, trans_img.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, border_value);
        break;
    }
}

void Registration::showCombinedImage() {
    //cv::imshow("", trans_img);
    thread->showCombinedImage(trans_img.clone());
}
