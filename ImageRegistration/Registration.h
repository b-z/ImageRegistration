#pragma once
#include <opencv2\opencv.hpp>
#include <vector>
class RegistrationThread;
class Registration
{
public:
    enum TransformType {
        TRANSFORM_TRANSLATE = 0,
        TRANSFORM_ROTATE = 1,
        TRANSFORM_AFFINE = 2,
        TRANSFORM_PERSPECTIVE = 3
    };
    enum SimilarityType {
        SIMILARITY_L1 = 0,
        SIMILARITY_L2 = 1,
        SIMILARITY_LINF = 2
    };
    enum OptimizationType {
        OPTIMIZE_NAIVE = 0,
        OPTIMIZE_GA = 1
    };
    Registration(RegistrationThread* thr, cv::Mat ref, cv::Mat tar, TransformType t, SimilarityType s, OptimizationType o);
    ~Registration();

    double getSimilarity(cv::Mat img1, cv::Mat img2, SimilarityType s);
    void applyTransform();
    void showTransformedImage();
    void runRegistration();
    void initialize();
    void optimizeNaive();
    void optimizeNaiveHelper(int pos);
public:
    int iter;
    double loss;
    cv::Mat ref_ori_img;
    cv::Mat tar_ori_img;
    cv::Mat trans_ori_img;
    cv::Mat ref_img; // reference image
    cv::Mat tar_img; // target image
    cv::Mat trans_img; // transformed image
    cv::Mat transform; // warp matrix 2 * 3
    cv::Scalar border_value; // average color of tar_img
    TransformType transform_type;
    SimilarityType similarity_type;
    OptimizationType optimization_type;
    RegistrationThread* thread;
    std::vector<float> params;
    std::vector<float> steps;
    std::vector<std::pair<float, float>> limits;
};

