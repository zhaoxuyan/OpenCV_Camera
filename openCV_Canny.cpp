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
    VideoWriter video("canny.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height));

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