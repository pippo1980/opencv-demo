#include <iostream>
#include <opencv2/opencv.hpp>

const int iterations = 40;
const int scale = 2;
const int temporalAreaRadius = 10;

static bool ori_image(cv::Ptr<cv::superres::FrameSource> &frames, int skip, std::string output) {

    cv::Mat ori_image;
    for (int i = 0; i < skip; i++) {
        frames.get()->nextFrame(ori_image);
        if (ori_image.cols == 0) {
            return false;
        }
    }

    frames.get()->nextFrame(ori_image);
    std::string name = output + "_ori_.png";
    cv::imwrite(name, ori_image);
    std::cout << "write:" << name << std::endl;

    return true;
}

static bool process(cv::Ptr<cv::superres::FrameSource> &frames, int skip, std::string output) {


    cv::Mat ori_image;
    for (int i = 0; i < skip; i++) {
        frames.get()->nextFrame(ori_image);

        if (ori_image.cols == 0) {
            return false;
        }
    }

    cv::Ptr<cv::superres::SuperResolution> super_res = cv::superres::createSuperResolution_BTVL1();
    super_res->setIterations(iterations);
    super_res->setScale(scale);
    super_res->setTemporalAreaRadius(temporalAreaRadius);
    super_res->setInput(frames);

    cv::Mat super_resolved_image;
    super_res->nextFrame(super_resolved_image);

    std::string name = output + "_super_.png";
    cv::imwrite(name, super_resolved_image);
    std::cout << "write:" << name << std::endl;

    cv::Mat dst = cv::Mat::zeros(ori_image.rows,
                                 ori_image.cols,
                                 CV_8UC4);
    cv::resize(super_resolved_image, dst, dst.size());

    name = output + "_super_resize_.png";
    cv::imwrite(name, dst);
    std::cout << "write:" << name << std::endl;

    return true;
}

int main(int argc, char **argv) {
    const std::string inputVideoName = "output.mp4";
    const int skip = 250;

    cv::Ptr<cv::superres::FrameSource> frames = cv::superres::createFrameSource_Video(inputVideoName);

    cv::Mat ori_image;
    frames.get()->nextFrame(ori_image);
    std::string name = inputVideoName + "_ori_.png";
    cv::imwrite(name, ori_image);
    std::cout << "write:" << name << std::endl;

    frames = cv::superres::createFrameSource_Video(inputVideoName);

    //    cv::Mat ori_image;
    //    frames.get()->nextFrame(ori_image);
    //    cv::imwrite("ori_image.png", ori_image);
    //
    //    frames.get()->reset();

    //    int i = 0;
    //    bool flag = true;
    //    while (flag) {
    //        std::string name = inputVideoName + "_" + std::to_string(i);
    //        flag = ori_image(frames, skip, name);
    //        i++;
    //    }
    //
    //    frames.get()->reset();
    //
    //    i = 0;
    //    flag = true;
    //    while (flag) {
    //        std::string name = inputVideoName + "_" + std::to_string(i++);
    //        flag = process(frames, skip, name);
    //    }

    // process(frames, 0, "output.mp4");

    cv::Ptr<cv::superres::SuperResolution> super_res = cv::superres::createSuperResolution_BTVL1();
    super_res->setIterations(iterations);
    super_res->setScale(scale);
    super_res->setTemporalAreaRadius(temporalAreaRadius);
    super_res->setInput(frames);

    cv::Mat super_resolved_image;
    super_res->nextFrame(super_resolved_image);

    name = inputVideoName + "_super_.png";
    cv::imwrite(name, super_resolved_image);
    std::cout << "write:" << name << std::endl;

//    cv::Mat dst = cv::Mat::zeros(320,
//                                 ori_image.cols,
//                                 CV_8UC4);
//    cv::resize(super_resolved_image, dst, dst.size());
//
//    name = output + "_super_resize_.png";
//    cv::imwrite(name, dst);
//    std::cout << "write:" << name << std::endl;

}