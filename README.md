# 第7周课程作业任务:

#### 1. 使用opencv 编程显示一张图片，打开一个名为"logo.txt"的文本文件（其中只有一行文本文件，包括你自己的名字和学号），然后编程读取汉字24*24点阵字形字库（HZKf2424.hz），把自己的名字和学号图形叠加到图片右下位置。

![](https://ws2.sinaimg.cn/large/006tKfTcgy1fqsox0izctj3060062glr.jpg)

- 参照《汉字点阵字库原理》中的写法添加头文件，报错：

![](https://ws4.sinaimg.cn/large/006tKfTcgy1fqsiom5vqij30mw05wjsd.jpg)

- 在Stackoverflow搜索发现，`graphics.h`这个库是在DOS下使用的，历史已经十分久远。故弃之。

![](https://ws2.sinaimg.cn/large/006tKfTcgy1fqsintd8n2j31680j4q8q.jpg)

- 在Mac下可使用`include<opencv2/imgproc.hpp>` 替代`graphics.h`
- 代码如下：

```c++
//使用opencv 编程显示一张图片，打开一个名为"logo.txt"的文本文件
//然后编程读取汉字24 * 24点阵字形字库（HZKf2424.hz），把自己的名字和学号图形叠加到图片右下位置。
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#define JIANJUCANSHU 2
using namespace cv;
unsigned char mat[24][3], Chinese[6];
FILE *HZKstream, *LogoFile;//
Point p;//绘点
void drawname(int a, int b, Mat img);

int main() {
    //读姓名学号文件 点阵字库文件
    if ((LogoFile = fopen("/Users/zhaoxuyan/Documents/多媒体技术/第7周/logo(示例).txt", "rt")) == nullptr)exit(0);
    //读点阵字库文件
    if ((HZKstream = fopen("/Users/zhaoxuyan/Documents/多媒体技术/第7周/中文点阵字库/HZK24F/HZKf2424.hz", "rb")) == nullptr)exit(0);

    //汉字用点阵字库  数字用puttext函数
    char ch;//读出Logo文件单个字符
    char ch1[6];//存储姓名
    char number[12];//存储学号

    //完成各属性赋值
    int i = 0, j = 0;//临时变量
    while (EOF != (ch = static_cast<char>(fgetc(LogoFile)))) {
        if (i <= 5) {
            ch1[i] = ch;
            i++;
        } else {
            number[j] = ch;
            i++;
            j++;
        }
    }
    for (int i = 0; i < 6; i++) {
        Chinese[i] = (unsigned char) ch1[i];
    }
    //1:根据ch1[4]去汉字点阵字库读汉字
    Mat img = imread("taaarannn.png");
    drawname(0, 1, img);
    drawname(2, 3, img);
    drawname(4, 5, img);

    //2:根据number去puttext到图片上
    putText(img, number, Point(550, 820), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 3, 8);//在图片上写文字

    imshow("result.png", img);
    imwrite("result.png", img);
    waitKey(0);
    fclose(HZKstream);

    //关闭文件 释放资源
    if (!(fclose(LogoFile) || fclose(HZKstream)))//关闭成功返回0
    {
        return 0;
    } else {
        return -1;
    }
}

void drawname(int a, int b, Mat img) {
    int i = 0, j = 0;
    i = Chinese[a] - 0xa0;
    j = Chinese[b] - 0xa0;
    fseek(HZKstream, (94 * (i - 1 - 15) + (j - 1)) * 72L, SEEK_SET);
    fread(mat, 72, 1, HZKstream);
    for (i = 0; i < 24; i++) {
        for (j = 0; j < 24; j++) {
            if ((0x80 >> i % 8) & mat[j][i / 8]) {
                p.x = j + 400 + b / JIANJUCANSHU * 50;
                p.y = i + 800;
                //画实心点
                circle(img, p, 1, Scalar(0, 255, 255), 1); 
            }
        }
    }
}

```

- 结果如下：

![](https://ws1.sinaimg.cn/large/006tKfTcgy1fqsq3dwkzij310616caig.jpg)



#### 2. 使用opencv打开摄像头或视频文件，实时显示原始视频，将视频每一帧依次做灰度转换、高斯滤波、canny边缘检测处理（原始视频和这3个中间步骤处理结果分别在一个窗口显示），最后将边缘检测结果保存为一个视频avi文件。

- 代码

```c++
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main() {

    // Create a VideoCapture object and use camera to capture the video
    VideoCapture cap(0);

    // Check if camera opened successfully
    if (!cap.isOpened()) {
        cout << "Error opening video stream" << endl;
        return -1;
    }

    // Default resolution of the frame is obtained.The default resolution is system dependent.
    auto frame_width = static_cast<int>(cap.get(CV_CAP_PROP_FRAME_WIDTH));
    auto frame_height = static_cast<int>(cap.get(CV_CAP_PROP_FRAME_HEIGHT));

    // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file.
    VideoWriter video("outcpp.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height));

    Mat edges;
    while (true) {
        Mat frame;

        // Capture frame-by-frame
        cap >> frame;

        // If the frame is empty, break immediately
        if (frame.empty())
            break;

        cvtColor(frame, edges, COLOR_BGR2GRAY);
        GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        Canny(edges, edges, 0, 30, 3);

        // Write the frame into the file 'outcpp.avi'
        video.write(frame);

        // Display the initial frame
        imshow("Frame", frame);
        // Display the resulting edges
        imshow("Edges", edges);

        // Press  ESC on keyboard to  exit
        auto c = (char) waitKey(1);
        if (c == 27)
            break;
    }

    // When everything done, release the video capture and write object
    cap.release();
    video.release();

    // Closes all the windows
    destroyAllWindows();
    return 0;
}
```






#### 3. 使用opencv打开摄像头，将摄像头对准人脸，学习opencv自带face-detection范例代码，编程实现人脸检测；在检测到的人脸区域，画一个红色圆圈，将最终结果保存为一个视频文件。

- 代码

```c++
#include <opencv2/opencv.hpp>

using namespace cv;
int main() {
    Mat img;
    Mat grayscaleFrame;
    CascadeClassifier face_cascade;
    //绝对路径，将xml文件放在相应文件里
    face_cascade.load("/Users/zhaoxuyan/anaconda/share/OpenCV/haarcascades/haarcascade_frontalface_alt2.xml");
    VideoCapture cam(0);
    if (!cam.isOpened()) exit(0);
    while (true) {
        cam >> img;
        cvtColor(img, grayscaleFrame, CV_BGR2GRAY);
        equalizeHist(grayscaleFrame, grayscaleFrame);
        std::vector <Rect> faces;
        face_cascade.detectMultiScale(grayscaleFrame, faces, 1.1, 3, 0, Size(20, 20));
        for (int i = 0; i < faces.size(); i++) {
            Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
            Point pt2(faces[i].x, faces[i].y);
            rectangle(img, pt1, pt2, cvScalar(0, 255, 255, 0), 2, 8, 0);
        }
        imshow("Camera", img);
        if(waitKey(30) >= 0) break;
    }
    return 0;
}


```

- 结果

![](https://ws3.sinaimg.cn/large/006tKfTcgy1fqst8tidc8j31kw0wzws8.jpg)

#### 4. 基于任务3，只对检测到的人脸区域做高斯模糊处理，将结果保存为一个视频文件。

- 代码

```c++
/*
基于任务3，只对检测到的人脸区域做高斯模糊处理，将结果保存为一个视频文件
*/
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void processimageGaosi(Mat &frame);

int main() {
    Mat frame;
    //读取视频或摄像头
    VideoCapture capture(0);

    //读取人脸数据
    CascadeClassifier stFaceCascade;
    if (!stFaceCascade.load("/Users/zhaoxuyan/anaconda/share/OpenCV/haarcascades/haarcascade_frontalface_alt2.xml")) {
        printf("Loading cascade error\n");
        return -1;
    }
    //视频保存
    auto frame_width = static_cast<int>(capture.get(CV_CAP_PROP_FRAME_WIDTH));
    auto frame_height = static_cast<int>(capture.get(CV_CAP_PROP_FRAME_HEIGHT));
    VideoWriter video("face_dectection_blur.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height));


    //处理视频
    while (true) {

        capture >> frame;

        if (!frame.empty()) {
            //frame经过检测算法
            auto *transIplimage = new IplImage(frame);
            std::vector<Rect> faceRects;//矩形描绘
            stFaceCascade.detectMultiScale(frame,
                                           faceRects,            //检出结果
                                           1.1,                  //缩放步长
                                           2,                    //框融合时的最小检出个数
                                           0 |
                                           CV_HAAR_SCALE_IMAGE,//标志 |CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_DO_ROUGH_SEARCH|CV_HAAR_DO_CANNY_PRUNING
                                           Size(100, 100),         //最小人脸尺寸
                                           Size(500, 500));     //最大人脸尺寸
            printf("Face Num[%lu]\n", faceRects.size());

            for (auto &faceRect : faceRects) {
                //画矩形图片， 左上角， 右下角， 颜色， 线条粗细， 线条类型，点类型
                cvRectangle(transIplimage,
                            cvPoint(faceRect.x, faceRect.y),
                            cvPoint(faceRect.x + faceRect.width, faceRect.y + faceRect.height),
                            cvScalar(0, 255, 0),
                            2, 8, 0);

                Mat image = cv::cvarrToMat(transIplimage);//整张图
                Rect rect(faceRect.x, faceRect.y, faceRect.width, faceRect.height);//选中指定区域
                Mat image_roi = image(rect);//选出感兴趣的区域
                //截取图像高斯处理
                processimageGaosi(image_roi);
                imshow("area", image_roi);
                //将感兴趣区域图像处理结果粘贴到原位置
                image_roi.copyTo(image_roi);
                video.write(image);
            }
            imshow("face_detection_blur", cv::cvarrToMat(transIplimage));
        }

        if (waitKey(30) == 27)   //延时30
            break;
    }
    return 0;
}

void processimageGaosi(Mat &frame) {
    //高斯滤波
    GaussianBlur(frame, frame, Size(99, 99), 0, 0);
}
```



- 结果

![](https://ws2.sinaimg.cn/large/006tKfTcgy1fqtkng35r4j31kw0wzk7v.jpg)

#### 5. 图文形式记录任务1-4的实验步骤，写入实验报告。

以上。

#### 6.实验心得

通过本次实验，环境配置方面已经是轻车熟路。带给我更大的体会是写程序调库时因为版本的不同，所带来的麻烦是巨大的。我使用的是openCV 3.0.0，与老师建议的openCV 2.x版本在头文件，函数的使用上面有诸多的不同，导致我花了大量时间搜索较新的代码语法，例如将Mat转为IplImage指针的语法，老版本是`IplImage* transIplimage = cvCloneImage(&(IplImage)frame);`，新版本则简单得多`auto *transIplimage = new IplImage(frame);`。反之是`cv::Mat m1 = cv::cvarrToMat(ipl);` 相较于老版本，3.0.0更为简单和方便，但是网上文档资源较旧版本来说较少，这也是对科学搜索能力的一种锻炼。本次实验还是相当有意思的，涉及到的点阵字库，人脸检测，高斯滤波，Canny边缘检测，这些算法实现虽然是简单的调库，但是最后要得出满意的效果也是不容易的。这对编程能力也是一种锻炼。总之，收获很大。
