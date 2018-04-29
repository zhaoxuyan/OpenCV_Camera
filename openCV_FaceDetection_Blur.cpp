/*
基于任务3，只对检测到的人脸区域做高斯模糊处理，将结果保存为一个视频文件
*/
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void processimageGaosi(Mat &frame);

//int main() {
//    Mat frame;
//    //读取视频或摄像头
//    VideoCapture capture(0);
//
//    //读取人脸数据
//    CascadeClassifier stFaceCascade;
//    if (!stFaceCascade.load("/Users/zhaoxuyan/anaconda/share/OpenCV/haarcascades/haarcascade_frontalface_alt2.xml")) {
//        printf("Loading cascade error\n");
//        return -1;
//    }
//    //视频保存
//    auto frame_width = static_cast<int>(capture.get(CV_CAP_PROP_FRAME_WIDTH));
//    auto frame_height = static_cast<int>(capture.get(CV_CAP_PROP_FRAME_HEIGHT));
//    VideoWriter video("face_dectection_blur.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height));
//
//
//    //处理视频
//    while (true) {
//
//        capture >> frame;
//
//        if (!frame.empty()) {
//            //frame经过检测算法
//            auto *transIplimage = new IplImage(frame);
//            std::vector<Rect> faceRects;//矩形描绘
//            stFaceCascade.detectMultiScale(frame,
//                                           faceRects,            //检出结果
//                                           1.1,                  //缩放步长
//                                           2,                    //框融合时的最小检出个数
//                                           0 |
//                                           CV_HAAR_SCALE_IMAGE,//标志 |CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_DO_ROUGH_SEARCH|CV_HAAR_DO_CANNY_PRUNING
//                                           Size(100, 100),         //最小人脸尺寸
//                                           Size(500, 500));     //最大人脸尺寸
//            printf("Face Num[%lu]\n", faceRects.size());
//
//            for (auto &faceRect : faceRects) {
//                //画矩形图片， 左上角， 右下角， 颜色， 线条粗细， 线条类型，点类型
//                cvRectangle(transIplimage,
//                            cvPoint(faceRect.x, faceRect.y),
//                            cvPoint(faceRect.x + faceRect.width, faceRect.y + faceRect.height),
//                            cvScalar(0, 255, 0),
//                            2, 8, 0);
//
//                Mat image = cv::cvarrToMat(transIplimage);//整张图
//                Rect rect(faceRect.x, faceRect.y, faceRect.width, faceRect.height);//选中指定区域
//                Mat image_roi = image(rect);//选出感兴趣的区域
//                //截取图像高斯处理
//                processimageGaosi(image_roi);
//                imshow("area", image_roi);
//                //将感兴趣区域图像处理结果粘贴到原位置
//                image_roi.copyTo(image_roi);
//                video.write(image);
//            }
//            imshow("face_detection_blur", cv::cvarrToMat(transIplimage));
//        }
//
//        if (waitKey(30) == 27)   //延时30
//            break;
//    }
//    return 0;
//}

void processimageGaosi(Mat &frame) {
    //高斯滤波
    GaussianBlur(frame, frame, Size(99, 99), 0, 0);
}