#include <opencv2/opencv.hpp>

using namespace cv;
//int main() {
//    Mat img;
//    Mat grayscaleFrame;
//    CascadeClassifier face_cascade;
//    //绝对路径，将xml文件放在相应文件里
//    face_cascade.load("/Users/zhaoxuyan/anaconda/share/OpenCV/haarcascades/haarcascade_frontalface_alt2.xml");
//    VideoCapture cam(0);
//    auto frame_width = static_cast<int>(cam.get(CV_CAP_PROP_FRAME_WIDTH));
//    auto frame_height = static_cast<int>(cam.get(CV_CAP_PROP_FRAME_HEIGHT));
//    VideoWriter video("face_dectection.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height));
//
//    if (!cam.isOpened()) exit(0);
//    while (true) {
//        cam >> img;
//        cvtColor(img, grayscaleFrame, CV_BGR2GRAY);
//        equalizeHist(grayscaleFrame, grayscaleFrame);
//        std::vector <Rect> faces;
//        face_cascade.detectMultiScale(grayscaleFrame, faces, 1.1, 3, 0, Size(20, 20));
//        for (int i = 0; i < faces.size(); i++) {
//            Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
//            Point pt2(faces[i].x, faces[i].y);
//            rectangle(img, pt1, pt2, cvScalar(0, 255, 255, 0), 2, 8, 0);
//        }
//        imshow("Camera", img);
//        video.write(img);
//        if(waitKey(30) >= 0) break;
//    }
//    return 0;
//}

