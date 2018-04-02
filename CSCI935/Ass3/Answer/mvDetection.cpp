/*------------------------------------------------------
Student's Name: Yixiang Fan
Student's number: 5083898
Student's email address: yf874@uowmail.edu.au
-------------------------------------------------------*/
#include<iostream>
#include<cmath>
#include"highgui.hpp"
using namespace std;

IplImage* pFrame;
IplImage* pItemp = NULL;
IplImage* pImg1 = NULL;		//Detected Moving Pixels
IplImage* pImg2 = NULL;		//Moving pixels after filtering
IplImage* pImg3 = NULL;		//Detected object (colour-coded)
IplImage* pBaImg = NULL;

CvMat* pMtemp = NULL;
CvMat* pMat1 = NULL;
CvMat* pMat2 = NULL;
CvMat* pMat3 = NULL;
CvMat* pBaMat = NULL;

//uchar* data = (uchar *)pImg3->imageData;
//int step = pImg3->widthStep / sizeof(uchar);
//int channels = pImg3->nChannels;

CvScalar color[3];
int k = 0;
void floodfill(int,int);

int main() {
	CvCapture* capture = cvCreateFileCapture("carpark_f6_compressed.avi");

	cvNamedWindow("Original Video Frame", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Detected Moving Pixels", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Moving pixels after filtering", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Detected object (colour-coded)", CV_WINDOW_AUTOSIZE);

	int threshold = 30;
	unsigned long numFrame = 0;
	double sum[25];
	color[0].val[0] = 255;
	color[0].val[1] = 0;
	color[0].val[2] = 0;
	color[1].val[0] = 0;
	color[1].val[1] = 255;
	color[1].val[2] = 0;
	color[2].val[0] = 0;
	color[2].val[1] = 0;
	color[2].val[2] = 255;

	while (pFrame = cvQueryFrame(capture)) {
		numFrame++;
		//initiate
		if (numFrame == 1) {

			pItemp = cvCreateImage(CvSize(pFrame->width, pFrame->height), IPL_DEPTH_8U, 1);
			pImg1 = cvCreateImage(CvSize(pFrame->width, pFrame->height), IPL_DEPTH_8U, 1);
			pImg2 = cvCreateImage(CvSize(pFrame->width, pFrame->height), IPL_DEPTH_8U, 1);
			pImg3 = cvCreateImage(CvSize(pFrame->width, pFrame->height), IPL_DEPTH_8U, 3);
			pBaImg = cvCreateImage(CvSize(pFrame->width, pFrame->height), IPL_DEPTH_8U, 1);

			pMtemp = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
			pMat1 = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
			pMat2 = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
			pMat3 = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
			pBaMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);

			cvCvtColor(pFrame, pItemp, CV_BGR2GRAY);
			cvCvtColor(pFrame, pBaImg, CV_BGR2GRAY);

			cvConvert(pItemp, pMtemp);
			cvConvert(pBaImg, pBaMat);

			cvMoveWindow("Original Video Frame", 0, 0);
			cvMoveWindow("Detected Moving Pixels", pFrame->width + 5, 0);
			cvMoveWindow("Moving pixels after filtering", 0, pFrame->height + 40);
			cvMoveWindow("Detected object (colour-coded)", pFrame->width + 5, pFrame->height + 40);

			//for (int n = 0; n < 5; n++) {
			//	for (int m = 0; m < 5; m++) {
			//		sum[n * 5 + m] = 0;
			//		for (int i = pFrame->height / 5 * n; i < pFrame->height / 5 * (n + 1); i++) {
			//			for (int j = pFrame->width / 5 * m; j < pFrame->width / 5 * (m + 1); j++) {
			//				sum[n * 5 + m] += cvGet2D(pMtemp, i, j).val[0];
			//			}
			//		}
			//	}
			//}
		}
		else {
			cvCvtColor(pFrame, pItemp, CV_BGR2GRAY);
			cvConvert(pItemp, pMtemp);

			cvSmooth(pMtemp, pMtemp, CV_GAUSSIAN, 3, 3, 0);

			//Detected Moving Pixels
			//double tempSum[25];
			//for (int n = 0; n < 5; n++) {
			//	for (int m = 0; m < 5; m++) {
			//		tempSum[n] = 0;
			//		for (int i = pFrame->height / 5 * n; i < pFrame->height / 5 * (n + 1); i++) {
			//			for (int j = pFrame->width / 5 * m; j < pFrame->width / 5 * (m + 1); j++) {
			//				tempSum[n * 5 + m] += cvGet2D(pMtemp, i, j).val[0];
			//				if (abs(tempSum[n * 5 + m] - sum[n * 5 + m]) > 500) {
			//					cvSet2D(pMat1, i, j, abs(cvGet2D(pMtemp, i, j).val[0] - cvGet2D(pBaMat, i, j).val[0]));
			//				}
			//				cvSet2D(pBaMat, i, j, cvGet2D(pMtemp, i, j).val[0] * 0.95 + cvGet2D(pBaMat, i, j).val[0] * 0.05);
			//			}
			//		}
			//		sum[n * 5 + m] = sum[n * 5 + m] * 0.05 + tempSum[n * 5 + m] * 0.95;
			//	}
			//}

			cvAbsDiff(pMtemp, pBaMat, pMat1);
			cvThreshold(pMat1, pMat1, 30, 255.0, CV_THRESH_BINARY);
			cvRunningAvg(pMtemp, pBaMat, 0.01, 0);
			cvConvert(pMat1, pImg1);

			//Moving pixels after filtering
			//cvCopy(pMat1, pMat2);
			cvConvert(pImg1, pImg2);
			cvErode(pImg2, pImg2, 0, 2);
			cvDilate(pImg2, pImg2, 0, 8);
			cvErode(pImg2, pImg2, 0, 6);

			//Detected object (colour-coded)
			cvConvert(pImg2, pMat3);
			cvConvert(pMat3, pItemp);
			
			cvZero(pImg3);
			//cvCvtColor(pImg2, pImg3, CV_GRAY2BGR);
			//CvPoint point;
			
			k = 0;
			//int colorNum = 0;
			for (int i = 0; i < pItemp->height; i++ ) {
				for (int j = 0; j < pItemp->width; j++) {
					if ((uchar)(pItemp->imageData + i * pItemp->widthStep)[j] == 255) {
						floodfill(i, j);
						k++;
						k = k % 3;
					}
					
					//if (cvGet2D(pMat3, i, j).val[0] == 255) {
					//	//point.x = i;
					//	//point.y = j;
					//	//cvFloodFill(pImg3, point, color[colorNum]);
					//	colorNum++;
					//	colorNum = colorNum % 10;
					//}
				}
			}
		}

		cvShowImage("Original Video Frame", pFrame);
		cvShowImage("Detected Moving Pixels", pImg1);
		cvShowImage("Moving pixels after filtering", pImg2);
		cvShowImage("Detected object (colour-coded)", pImg3);

		char c = cvWaitKey(33);
		if (c == 27) break;
	}
	cvDestroyWindow("Original Video Frame");
	cvDestroyWindow("Detected Moving Pixels");
	cvDestroyWindow("Moving pixels after filtering");
	cvDestroyWindow("Detected object (colour-coded)");
	cvReleaseCapture(&capture);
	cvReleaseImage(&pItemp);
	cvReleaseImage(&pImg1);
	cvReleaseImage(&pImg2);
	cvReleaseImage(&pImg2);
	cvReleaseImage(&pBaImg);
	cvReleaseMat(&pMtemp);
	cvReleaseMat(&pMat1);
	cvReleaseMat(&pMat2);
	cvReleaseMat(&pMat3);
	cvReleaseMat(&pBaMat);
	
	return 0;
}

void floodfill(int n, int m) {
	if (n >= pMat3->height || n < 0 || m >= pMat3->width || m < 0)
		return;
	uchar x = (pItemp->imageData + n * pItemp->widthStep)[m];
	if (x == 0 || x == 100)
		return;
	else if (x == 255) {
		(pItemp->imageData + n * pItemp->widthStep)[m] = 100;
		cvSet2D(pImg3, n, m, color[k]);
		//floodfill(n - 1, m);
		floodfill(n, m + 1);
		floodfill(n + 1, m);
		floodfill(n, m - 1);
	}
}

