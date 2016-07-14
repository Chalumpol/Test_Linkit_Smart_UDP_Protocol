#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

using namespace cv;
using namespace std;

Mat adjusted_color_img;
Mat frame;

int iLowH = 31;
int iHighH = 87;

int iLowS = 165;
int iHighS = 255;

int iLowV = 35;
int iHighV = 255;

char buffer[80];

const double IMAGE_FIXED_AREA = 32000.0;

static float x_pos;
static float y_pos;
static float ratio_1;

int clientSocket, portNum, nBytes;
struct sockaddr_in serverAddr;

socklen_t addr_size;



Mat brightness_and_contrast(Mat img)
{
/// Initialize values
  cv::Mat new_image = cv::Mat::zeros( img.size(), img.type() );
  // cv::cvtColor(img, new_image, CV_BGR2GRAY); //Convert the captured frame from BGR to HSV
  float alpha = 1.3;
  int beta = -40;
// use this method to adjust color and contrast
  img.convertTo(new_image, -1, alpha, beta);
//show the new image
  GaussianBlur(new_image, new_image, Size( 7, 7), 0, 0);
  imshow("adjusted color", new_image);

/// Show stuff
  // imshow("Original Image", img);
  // cv::imshow("New Image", new_image);
  return new_image;
/// Wait until user press some key

}

void color_detection(cv::Mat img)
{
  cv::Mat imgROI = img;
  vector<vector<cv::Point> > contours;
  vector<cv::Vec4i> hierarchy;
  cv::Mat imgHSV;
  float offset_x;
  float offset_y;
  float area = 0.0;
  int largest_area = 0;
  int largest_contour_index = 0;
  cv::namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
  cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
  cvCreateTrackbar("HighH", "Control", &iHighH, 179);

  cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
  cvCreateTrackbar("HighS", "Control", &iHighS, 255);

  cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
  cvCreateTrackbar("HighV", "Control", &iHighV, 255);

  cv::cvtColor(imgROI, imgHSV, CV_RGB2HSV); //Convert the captured frame from BGR to HSV

  cv::Mat imgThresholded;

  cv::inRange(imgHSV, cv::Scalar(iLowH, iLowS, iLowV), cv::Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image with

  //morphological opening (remove small objects from the foreground)
  cv::erode(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3)) );
  // cv::dilate(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3)) );

  cv::imshow("Thresholded Image", imgThresholded); //show the thresholded image

  // ROI_y = img.rows*13.0/100.00;    //Percentage by which orgin of the ROI has to be shifted in y direction.
  // ROI_width = img.cols; //Width of the ROI
  // ROI_height = img.rows*10.0/100.00;

  // imgROI=imgThresholded(cv::Rect(0, ROI_y, ROI_width, ROI_height)); //Get the region of interest(ROI)
  // // Find the oplygon in third order
  // cv::Moments mu = moments(imgThresholded, true);
  // // Find the center of coordinate

  // cv::Canny( imgThresholded, imgCanny, 100, 500, 3 );

  // cv::imshow("Canny Image", imgCanny); //show the thresholded image
  // Find the contour of Thresholded
  findContours( imgThresholded, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
  // /// Get the moments
  // vector<cv::Moments> mu(contours.size() );
  // for ( int i = 0; i < contours.size(); i++ )
  // { mu[i] = moments( contours[i], false );}

  // // ///  Get the mass centers:
  // vector<cv::Point2f> mc( contours.size() );
  // for ( int i = 0; i < contours.size(); i++ )
  // { mc[i] = cv::Point2f( mu[i].m10 / mu[i].m00 , mu[i].m01 / mu[i].m00 ); }

  // find the largest area (contour)
  for ( int i = 0; i < contours.size(); i++ )
  {
    // area += mu2.m00;
    double area = contourArea( contours[i] );  //  Find the area of contour

    if ( area > largest_area )
    {
      largest_area = area;
      largest_contour_index = i;               //Store the index of largest contour
    }
    else
    {
      // break();
    }
// double area = cv::contourArea(contours);
  }
  // Classified if the largest contour is less than 1 (no interest area)
  if (largest_area > 0) {
    cv::Moments mu = moments(contours[largest_contour_index], true);
    cv::Point2f center(mu.m10 / mu.m00, mu.m01 / mu.m00);
    offset_x = (1 - 2 * center.x / imgThresholded.cols);
    offset_y = (1 - 2 * center.y / imgThresholded.rows);
    x_pos = offset_x;
    y_pos = offset_y;
  }
  else
  {
    largest_area = 0;
  }
  // Draw the center center and rectangle
  circle(imgROI, cv::Point(imgThresholded.cols / 2, imgThresholded.rows / 2), 10, CV_RGB(255, 0, 0));
  // cv::rectangle(imgROI,cv::Point((imgThresholded.cols/2)-100, (imgThresholded.rows/2)-100),cv::Point((imgThresholded.cols/2)+100, (imgThresholded.rows/2)+100),CV_RGB(0,0,255),-1,8);
  line(imgROI, cv::Point((imgThresholded.cols / 2) - 100, (imgThresholded.rows / 2) - 100), cv::Point((imgThresholded.cols / 2) - 100, (imgThresholded.rows / 2) + 100), CV_RGB(0, 0, 255), 1, 8);
  line(imgROI, cv::Point((imgThresholded.cols / 2) - 100, (imgThresholded.rows / 2) + 100), cv::Point((imgThresholded.cols / 2) + 100, (imgThresholded.rows / 2) + 100), CV_RGB(0, 0, 255), 1, 8);
  line(imgROI, cv::Point((imgThresholded.cols / 2) + 100, (imgThresholded.rows / 2) + 100), cv::Point((imgThresholded.cols / 2) + 100, (imgThresholded.rows / 2) - 100), CV_RGB(0, 0, 255), 1, 8);
  line(imgROI, cv::Point((imgThresholded.cols / 2) + 100, (imgThresholded.rows / 2) - 100), cv::Point((imgThresholded.cols / 2) - 100, (imgThresholded.rows / 2) - 100), CV_RGB(0, 0, 255), 1, 8);
  //find the ratio of the interested area
  double ratio = largest_area / IMAGE_FIXED_AREA;

  if (isnan(offset_x) || isnan(offset_y))
  {
    cout << "have a nan number" << endl;
    x_pos = 0;
    y_pos = 0;
  }
  else if (largest_area <= 5000)
  {
    cout << "Area of interest is not enough to calculate" << endl;
    x_pos = 0;
    y_pos = 0;
  }
  else
  {
    //Draw to the senter of the largest area of interest.
    circle(imgROI, cv::Point(320 - (offset_x * 320), 240 - (offset_y * 240)), 20, CV_RGB(255, 0, 255));
    line(imgROI, cv::Point( imgThresholded.cols / 2, imgThresholded.rows / 2 ), cv::Point(320 - (offset_x * 320), 240 - (offset_y * 240)), CV_RGB(255, 0, 100), 3, 2 );

  }
  cout << "Area = " << largest_area << endl;
  cout << "ratio = " << ratio << endl;
  cout << "x_offset = " << x_pos << endl;
  cout << "y_offset = " << y_pos << endl;
  imshow("ROI", imgROI); //show the original image

  //Send Data to UDP Server (Linkit Smart)

  sprintf(buffer, "x_pos_offset = %f", x_pos);

  nBytes = strlen(buffer) + 1;

  sendto(clientSocket, buffer, nBytes, 0, (struct sockaddr *)&serverAddr, addr_size);

  sprintf(buffer, "y_pos_offset = %f", y_pos);

  nBytes = strlen(buffer) + 1;

  sendto(clientSocket, buffer, nBytes, 0, (struct sockaddr *)&serverAddr, addr_size);

  sprintf(buffer, "ratio = %f", ratio);

  nBytes = strlen(buffer) + 1;

  sendto(clientSocket, buffer, nBytes, 0, (struct sockaddr *)&serverAddr, addr_size);
// return imgThresholded;
}



int main(int argc, char* argv[])
{
  VideoCapture cap; //
  cap.open("http://192.168.1.139:1234/?action=stream");
  if (!cap.isOpened())  // if not success, exit program
  {
    cout << "Cannot open the video cam" << endl;
    return -1;
  }

  clientSocket = socket(PF_INET, SOCK_DGRAM, 0);
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(33333);
  serverAddr.sin_addr.s_addr = inet_addr("192.168.1.139");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
  addr_size = sizeof serverAddr;

  while (1)
  {
    cap.grab();
    cap.retrieve(frame);
    adjusted_color_img = brightness_and_contrast(frame);
    color_detection(adjusted_color_img);
    imshow("view", frame);
    waitKey(20);
    usleep(2000);
  }
}