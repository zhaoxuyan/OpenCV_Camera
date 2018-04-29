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

//int main() {
//    //读姓名学号文件 点阵字库文件
//    if ((LogoFile = fopen("/Users/zhaoxuyan/Documents/多媒体技术/第7周/logo(示例).txt", "rt")) == nullptr)exit(0);
//    //读点阵字库文件
//    if ((HZKstream = fopen("/Users/zhaoxuyan/Documents/多媒体技术/第7周/中文点阵字库/HZK24F/HZKf2424.hz", "rb")) == nullptr)exit(0);
//
//    //汉字用点阵字库  数字用puttext函数
//    char ch;//读出Logo文件单个字符
//    char ch1[6];//存储姓名
//    char number[12];//存储学号
//
//    //完成各属性赋值
//    int i = 0, j = 0;//临时变量
//    while (EOF != (ch = static_cast<char>(fgetc(LogoFile)))) {
//        if (i <= 5) {
//            ch1[i] = ch;
//            i++;
//        } else {
//            number[j] = ch;
//            i++;
//            j++;
//        }
//    }
//    for (int i = 0; i < 6; i++) {
//        Chinese[i] = (unsigned char) ch1[i];
//    }
//    //1:根据ch1[4]去汉字点阵字库读汉字
//    Mat img = imread("taaarannn.png");
//    drawname(0, 1, img);
//    drawname(2, 3, img);
//    drawname(4, 5, img);
//
//    //2:根据number去puttext到图片上
//    putText(img, number, Point(550, 820), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 3, 8);//在图片上写文字
//
//    imshow("result.png", img);
//    imwrite("result.png", img);
//    waitKey(0);
//    fclose(HZKstream);
//
//    //关闭文件 释放资源
//    if (!(fclose(LogoFile) || fclose(HZKstream)))//关闭成功返回0
//    {
//        return 0;
//    } else {
//        return -1;
//    }
//}

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
