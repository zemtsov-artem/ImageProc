//
//  rgbtogray.cpp
//  Black-white(lab1)
//
//  Created by артем on 03.03.17.
//  Copyright © 2017 артем. All rights reserved.
//
//Some describe
//GI - gray image
//Arr - array
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"
#include "src/hist.cpp"
#include "src/rgbtogray.cpp"
#include "src/graytobin.cpp"

using namespace cv;
using namespace std;

int main( )
{
    Mat img = imread("vova.jpg");
    if(! img.data ) {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    
    
    // rgb to gray scale
    Mat grayImg = intensity(img);
    // get histogram for gray scale
    Mat hist = getHist(grayImg);
    // declarate and init ptr and temrary min
    cv::Mat_<uchar> ptr = hist;
    cv::Mat_<uchar> GrayPtr = grayImg;
    // declarate arr
    uint *histArr = new uint[255];
    
    // init arr and filling from gray image
    initHistArr(histArr);
    fillArrayWithValuesFromGI(histArr, grayImg);
    
    // the declaration of the flags of the describing min an max
    uint leftFlag = 256, rightFlag = 0;
    findMaxValueInHistArrayAndFixIndex(histArr, &leftFlag);
    findMinValueInHistArrayAndFixIndex(histArr, &rightFlag);
    
    // declarate
    ushort barrierObtainedByTheMethodOfTheTriangle = -1;
    ushort SimpleBarrier = (rightFlag+leftFlag)/2;
    
    barrierObtainedByTheMethodOfTheTriangle = findMaxDistanceFromLineToSomePoint(
                                                                                 leftFlag,
                                                                                 rightFlag,
                                                                                 histArr);
    
    
    if ( checkCorrect(barrierObtainedByTheMethodOfTheTriangle,0,255)) {
        cout<<barrierObtainedByTheMethodOfTheTriangle<<" - unknownBarrier"<<endl;
    }
    else {
        cout<<"Wrong barrier"<<endl;
    }
    // declarate new mat to save new binary images
    Mat CoolBlackAndWhiteImage,SimpleBlackAndWhiteImage;
    
    grayImg.copyTo(CoolBlackAndWhiteImage);
    grayImg.copyTo(SimpleBlackAndWhiteImage);
    Mat_<uchar> blackAndWhiteImagePtr = CoolBlackAndWhiteImage;
    Mat_<uchar> SimpleBlackAndWhiteImagePtr = SimpleBlackAndWhiteImage;
    
  
    // our method to convert image to black and white
    for (int i  = 0 ; i < blackAndWhiteImagePtr.rows; i++) {
        for (int j = 0 ; j < blackAndWhiteImagePtr.cols; j++) {
            if (blackAndWhiteImagePtr(i,j) > barrierObtainedByTheMethodOfTheTriangle) {
                blackAndWhiteImagePtr(i,j)= 255;
            }else {
                blackAndWhiteImagePtr(i,j)= 0;
            }
            }
    }
    // simple convertation method
    for (int i  = 0 ; i < SimpleBlackAndWhiteImagePtr.rows; i++) {
        for (int j = 0 ; j < SimpleBlackAndWhiteImagePtr.cols; j++) {
            if (SimpleBlackAndWhiteImagePtr(i,j) > SimpleBarrier) {
                SimpleBlackAndWhiteImagePtr(i,j)= 255;
            }else {
                SimpleBlackAndWhiteImagePtr(i,j)= 0;
            }
        }
    }
    
    
    
    // show the pixels of the difference in 2 different methods
    Mat ImageForShowDiff;
    img.copyTo(ImageForShowDiff);
    Mat_<Vec3b> newPtr = ImageForShowDiff;
    
//    for (int i  = 0 ; i < newPtr.rows; i++) {
//        for (int j = 0 ; j < newPtr.cols; j++) {
//            if (SimpleBlackAndWhiteImagePtr(i,j) == blackAndWhiteImagePtr(i,j)) {
//                if (SimpleBlackAndWhiteImagePtr(i,j) == 255) {
//                    //ImageForShowDiff.at<Vec3b>(i,j)=Vec3b(255,255,255);
//                    newPtr(i,j)=Vec3b(255,255,255);
//                }
//                else {
//                    //ImageForShowDiff.at<Vec3b>(i,j)=Vec3b(0,0,0);
//                    newPtr(i,j)=Vec3b(0,0,0);
//                }
//            }
//            else {
//                //ImageForShowDiff.at<Vec3b>(i,j)=Vec3b(255,0,0);
//                newPtr(i,j)=Vec3b(255,0,0);
//            }
//        }
//    }
    
    
    for (int i  = 0 ; i < newPtr.rows; i++) {
        for (int j = 0 ; j < newPtr.cols; j++) {
            if (j%2) {
                newPtr(i,j)=Vec3b(255,255,255);
            }
            
        }
    }
    imshow("CoolBaw", CoolBlackAndWhiteImage);
    imshow("SimpleBaw",SimpleBlackAndWhiteImage);
    imshow("Difference",ImageForShowDiff);
    waitKey(0);
    return 0;
}

