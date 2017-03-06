//
//  graytobin.cpp
//  Black-white(lab1)
//
//  Created by артем on 03.03.17.
//  Copyright © 2017 артем. All rights reserved.
//

#include <stdio.h>

// init arr
void initHistArr(uint *_histArr){
    for (int i =0; i<256; i++) {
        *(_histArr + i) = 0;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
void fillArrayWithValuesFromGI(uint *_histArr ,Mat _grayScaleImageMatrix){
    Mat_<uchar> grayScaleImageMatrixPtr = _grayScaleImageMatrix;
    for (int i =0; i<_grayScaleImageMatrix.rows; i++) {
        for (int j = 0; j < _grayScaleImageMatrix.cols; j++) {
            *(_histArr+grayScaleImageMatrixPtr(i,j))+=1;
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
void printHistArray(uint *_histArr){
    for (int i =0; i<256; i++) {
        std::cout<<*(_histArr+i)<<" - "<<i<<std::endl;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
uint findMinValueInHistArrayAndFixIndex(uint *_histArr,uint *_ptrToTheFlagVariable) {
    uint tempMin = *(_histArr);
    for (int i =0; i<256; i++) {
        if (*(_histArr+i) < tempMin ) {
            tempMin = *(_histArr+i);
            *(_ptrToTheFlagVariable) = i;
        }
        
    }
    return tempMin;
}
//////////////////////////////////////////////////////////////////////////////////////////
uint findMaxValueInHistArrayAndFixIndex(uint* _histArr,uint *_ptrToTheFlagVariable) {
    uint tempMax = *(_histArr);
    for (int i =0; i<256; i++) {
        if (*(_histArr+i) > tempMax ) {
            tempMax = *(_histArr+i);
            *(_ptrToTheFlagVariable) = i;
        }
        
    }
    return tempMax;
}
//////////////////////////////////////////////////////////////////////////////////////////
// find max distance from line that connecting 2 points to some point from the set
ushort findMaxDistanceFromLineToSomePoint(int _firstPoint,int _secondPoint,uint *_histArr) {
    int maxDistance = 0;
    int barrierObtainedByTheMethodOfTheTriangle = -1;

    for (int i = _firstPoint; i<(_secondPoint-_firstPoint); i++) {
        double tempValue =
        abs(
            (_firstPoint+i) / (_secondPoint - _firstPoint)+
            *(_histArr+_firstPoint+i) / (*(_histArr+_secondPoint) - *(_histArr+_firstPoint) ) -
            _firstPoint / (_secondPoint-_firstPoint) +
            *(_histArr+_firstPoint) / (*(_histArr+_secondPoint) - *(_histArr + _firstPoint) )
            )  /
        sqrt(
             (1 / pow(_secondPoint - _firstPoint, 2) ) +
             (1 / pow((*(_histArr + _secondPoint) - *(_histArr + _firstPoint)),2) )
             );
        if ( ((int)tempValue) > maxDistance ){
            maxDistance = (int)tempValue;
            barrierObtainedByTheMethodOfTheTriangle = _firstPoint + i ;
        }
    }
    return barrierObtainedByTheMethodOfTheTriangle;
}
//////////////////////////////////////////////////////////////////////////////////////////
int checkCorrect(int _value,int min,int max){
    if ( (_value <= max) && (_value >= min) ) {
        return true;
    }
    else return false;
}
//////////////////////////////////////////////////////////////////////////////////////////
void ConvertImageToBinaryWithBarrier(Mat_<uchar> _imagePtr,int _barrier ) {
    for (int i  = 0 ; i < _imagePtr.rows; i++) {
        for (int j = 0 ; j < _imagePtr.cols; j++) {
            if (_imagePtr(i,j) > _barrier) {
                _imagePtr(i,j)= 255;
            }else {
                _imagePtr(i,j)= 0;
            }
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
// p.s it is does not work, and i can not describe why is it ;(
void compareTwoUshortMat(Mat_<ushort> _firstMat,
                           Mat_<ushort> _secondMat,
                           uint _rows,uint _cols,
                           Mat _MatToStore) {
    std::cout << _MatToStore.rows << " - MatToStore rows" << std::endl; // some for debug
    std::cout << _MatToStore.cols << " - MatToStore cols" << std::endl; // some for debug
    std::cout<< _rows << " - rows" << std::endl;                       // some for debug
    std::cout << _cols << " - cols" << std::endl;                      // some for debug
    
    Mat_<Vec3b> MatToStorePtr = _MatToStore;
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            if ( (_firstMat(i,j) == _secondMat(i,j) ) && (_firstMat(i,j) == 255) ) {
                MatToStorePtr(i,j) = Vec3b(255,255,255);
            }
            if ( (_firstMat(i,j) == _secondMat(i,j) ) && (_firstMat(i,j) == 0) ) {
                MatToStorePtr(i,j) = Vec3b(0,0,0);
            }
            if (_firstMat(i,j) != _secondMat(i,j) ){
                MatToStorePtr(i,j) = Vec3b(255,0,0);
            }
                
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void compareTwoMat(const Mat firstMat, const Mat secondMat) {
    Mat differenceImage = firstMat.clone();
    for (int i = 0; i < differenceImage.rows; i++) {
        for (int j = 0; j < differenceImage.cols; j++) {
            if (firstMat.at<cv::Vec3b>(i, j) != secondMat.at<cv::Vec3b>(i, j)) {
                differenceImage.at<cv::Vec3b>(i, j) = Vec3b(255, 0, 0);
            } else {
                differenceImage.at<cv::Vec3b>(i, j) = firstMat.at<cv::Vec3b>(i, j);
            }
        }
    }
    
    imshow("Image difference", differenceImage);
}




