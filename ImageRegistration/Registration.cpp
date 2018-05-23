#include "stdafx.h"
#include "Registration.h"


Registration::Registration(cv::Mat ref, cv::Mat tar, TransformType t, SimilarityType s, OptimizationType o) {
    ref_img = ref;
    tar_img = tar;
    trans_img = cv::Mat(tar.rows, tar.cols, tar.type());
    transform_type = t;
    transform = cv::Mat(2, 3, CV_32FC1);
    border_value = cv::mean(tar_img);
    similarity_type = s;
    optimization_type = o;
}


Registration::~Registration()
{
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
    cv::warpAffine(ref_img, trans_img, transform, trans_img.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, border_value);
}

void Registration::showCombinedImage() {

}
