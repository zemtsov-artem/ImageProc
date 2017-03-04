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
    
    cout<<img.cols<<" simpleImg cols"<<endl;
    cout<<img.rows<<" simpleImg rows"<<endl;
    
    // rgb to gray scale
    Mat grayImg = intensity(img);
    // get histogram for gray scale
    Mat hist = getHist(grayImg);
    // declarate and init ptr and temrary min
    cv::Mat_<uchar> ptr = hist;
    cv::Mat_<uchar> GrayPtr = grayImg;

    // declarate arr
    uint *histArr = new uint[255];
    // init arr
    for (int i =0; i<256; i++) {
        *(histArr+i) = 0;
    }

    // compare our values and tempMin
    for (int i =0; i<grayImg.rows; i++) {
        for (int j = 0; j<grayImg.cols; j++) {
            *(histArr+GrayPtr(i,j))+=1;
        }
    }
//    //Show array
//    for (int i =0; i<256; i++) {
//        cout<<*(histArr+i)<<" - "<<i<<endl;
//    }
    
    int tempMin = grayImg.rows*grayImg.cols;
    int tempMax = 0;
    int leftFlag = 256, rightFlag = 0;
    
    // find min
    for (int i =0; i<256; i++) {
        if ( (*(histArr+i) < tempMin) ) {
            tempMin = *(histArr+i);
            rightFlag = i;
        }
    }
    
    // find max
    for (int i =0; i<256; i++) {
        if ( (*(histArr+i) > tempMax)) {
            tempMax = *(histArr+i);
            leftFlag = i;
        }
    }
    
    cout<< tempMin<<" - min and his num = "<<rightFlag<<endl;
    cout<< tempMax<<" - max and his num = "<<leftFlag<<endl;
    
    //уравнение прямой (x-x1)/(x2-x1) = (y-y1)/(y2-y1)
    
    int maxDistance = 0;
    int unknownIntesity = -1;
    
    for (int i = leftFlag; i<(rightFlag-leftFlag); i++) {
        double tempValue =
            abs(
                (leftFlag+i)/(rightFlag-leftFlag)+
                *(histArr+leftFlag+i)/(*(histArr+rightFlag) - *(histArr+leftFlag) ) -
                leftFlag/(rightFlag-leftFlag) +
                *(histArr+leftFlag)/(*(histArr+rightFlag) - *(histArr + leftFlag) )
                )  /
            sqrt(
                 (1 / pow(rightFlag-leftFlag, 2) ) +
                 (1 / pow((*(histArr+rightFlag) - *(histArr+leftFlag)),2) )
                 );
        if ( ((int)tempValue)>maxDistance ){
            maxDistance = (int)tempValue;
            unknownIntesity = leftFlag + i ;
        }
        
    }
    
    
    cout<<maxDistance<<" - maxDistance"<<endl;
    if ((unknownIntesity >=0 ) && (unknownIntesity<=255)) {
        cout<<unknownIntesity<<" -unknownIntensity"<<endl;
    }
    else {
        cout<<"Wrong instensity"<<endl;
    }
    
    Mat blackAndWhiteImage;

    grayImg.copyTo(blackAndWhiteImage);
    Mat_<uchar> blackAndWhiteImagePtr = blackAndWhiteImage;
    
    
    cout<<img.cols<<" - cols"<<endl;
    cout<<img.rows<<" - rows"<<endl;
    
    for (int i  = 0 ; i < blackAndWhiteImagePtr.rows; i++) {
        for (int j = 0 ; j < blackAndWhiteImagePtr.cols; j++) {
            if (blackAndWhiteImagePtr(i,j) > unknownIntesity) {
                blackAndWhiteImagePtr(i,j)= 255;
                
            }else {
                blackAndWhiteImagePtr(i,j)= 0;
            }
            }
    }
    
    
    imshow("baw", blackAndWhiteImage);
    waitKey(0);
    return 0;
}

