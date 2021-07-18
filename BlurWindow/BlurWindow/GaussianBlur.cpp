
#include "stdafx.h"

// void GaussianBlur(unsigned char* img,  unsigned int width, unsigned int height, unsigned int channels, unsigned int radius)
// {
// 	radius = min(max(1, radius), 248);
// 	unsigned int kernelSize = 1 + radius * 2;
// 	unsigned int* kernel = (unsigned int*)malloc(kernelSize* sizeof(unsigned int));
// 	memset(kernel, 0, kernelSize* sizeof(unsigned int));
// 	int(*mult)[256] = (int(*)[256])malloc(kernelSize * 256 * sizeof(int));
// 	memset(mult, 0, kernelSize * 256 * sizeof(int));
	 
// 	int	xStart = 0;
// 	int	yStart = 0;
// 	width = xStart + width - max(0, (xStart + width) - width);
// 	height = yStart + height - max(0, (yStart + height) - height);
// 	int imageSize = width*height;
// 	int widthstep = width*channels;
// 	if (channels == 3 || channels == 4)
// 	{
// 		unsigned char *    CacheImg = nullptr;
// 		CacheImg = (unsigned char *)malloc(sizeof(unsigned char) * imageSize * 6);
// 		if (CacheImg == nullptr) return;
// 		unsigned char *    rCache = CacheImg;
// 		unsigned char *    gCache = CacheImg + imageSize;
// 		unsigned char *    bCache = CacheImg + imageSize * 2;
// 		unsigned char *    r2Cache = CacheImg + imageSize * 3;
// 		unsigned char *    g2Cache = CacheImg + imageSize * 4;
// 		unsigned char *    b2Cache = CacheImg + imageSize * 5;
// 		int sum = 0;
// 		for (int K = 1; K < radius; K++){
// 			unsigned int szi = radius - K;
// 			kernel[radius + K] = kernel[szi] = szi*szi;
// 			sum += kernel[szi] + kernel[szi];
// 			for (int j = 0; j < 256; j++){
// 				mult[radius + K][j] = mult[szi][j] = kernel[szi] * j;
// 			}
// 		}
// 		kernel[radius] = radius*radius;
// 		sum += kernel[radius];
// 		for (int j = 0; j < 256; j++){
// 			mult[radius][j] = kernel[radius] * j;
// 		}
// 		for (int Y = 0; Y < height; ++Y) {
// 			unsigned char*     LinePS = img + Y*widthstep;
// 			unsigned char*     LinePR = rCache + Y*width;
// 			unsigned char*     LinePG = gCache + Y*width;
// 			unsigned char*     LinePB = bCache + Y*width;
// 			for (int X = 0; X < width; ++X) {
// 				int     p2 = X*channels;
// 				LinePR[X] = LinePS[p2];
// 				LinePG[X] = LinePS[p2 + 1];
// 				LinePB[X] = LinePS[p2 + 2];
// 			}
// 		}
// 		int kernelsum = 0;
// 		for (int K = 0; K < kernelSize; K++){
// 			kernelsum += kernel[K];
// 		}
// 		float fkernelsum = 1.0f / kernelsum;
// 		for (int Y = yStart; Y < height; Y++){
// 			int heightStep = Y * width;
// 			unsigned char*     LinePR = rCache + heightStep;
// 			unsigned char*     LinePG = gCache + heightStep;
// 			unsigned char*     LinePB = bCache + heightStep;
// 			for (int X = xStart; X < width; X++){
// 				int cb = 0;
// 				int cg = 0;
// 				int cr = 0;
// 				for (int K = 0; K < kernelSize; K++){
// 					unsigned    int     readPos = ((X - radius + K + width) % width);
// 					int * pmult = mult[K];
// 					cr += pmult[LinePR[readPos]];
// 					cg += pmult[LinePG[readPos]];
// 					cb += pmult[LinePB[readPos]];
// 				}
// 				unsigned int p = heightStep + X;
// 				r2Cache[p] = cr* fkernelsum;
// 				g2Cache[p] = cg* fkernelsum;
// 				b2Cache[p] = cb* fkernelsum;
// 			}
// 		}
// 		for (int X = xStart; X < width; X++){
// 			int WidthComp = X*channels;
// 			int WidthStep = width*channels;
// 			unsigned char*     LinePS = img + X*channels;
// 			unsigned char*     LinePR = r2Cache + X;
// 			unsigned char*     LinePG = g2Cache + X;
// 			unsigned char*     LinePB = b2Cache + X;
// 			for (int Y = yStart; Y < height; Y++){
// 				int cb = 0;
// 				int cg = 0;
// 				int cr = 0;
// 				for (int K = 0; K < kernelSize; K++){
// 					unsigned int   readPos = ((Y - radius + K + height) % height) * width;
// 					int * pmult = mult[K];
// 					cr += pmult[LinePR[readPos]];
// 					cg += pmult[LinePG[readPos]];
// 					cb += pmult[LinePB[readPos]];
// 				}
// 				int    p = Y*WidthStep;
// 				LinePS[p] = (unsigned char)(cr * fkernelsum);
// 				LinePS[p + 1] = (unsigned char)(cg * fkernelsum);
// 				LinePS[p + 2] = (unsigned char)(cb* fkernelsum);
 
				 
// 			}
// 		}
// 		free(CacheImg);
// 	}
// 	else if (channels == 1)
// 	{
// 		unsigned char *    CacheImg = nullptr;
// 		CacheImg = (unsigned char *)malloc(sizeof(unsigned char) * imageSize * 2);
// 		if (CacheImg == nullptr) return;
// 		unsigned char *    rCache = CacheImg;
// 		unsigned char *    r2Cache = CacheImg + imageSize;
 
// 		int sum = 0;
// 		for (int K = 1; K < radius; K++){
// 			unsigned int szi = radius - K;
// 			kernel[radius + K] = kernel[szi] = szi*szi;
// 			sum += kernel[szi] + kernel[szi];
// 			for (int j = 0; j < 256; j++){
// 				mult[radius + K][j] = mult[szi][j] = kernel[szi] * j;
// 			}
// 		}
// 		kernel[radius] = radius*radius;
// 		sum += kernel[radius];
// 		for (int j = 0; j < 256; j++){
// 			mult[radius][j] = kernel[radius] * j;
// 		}
// 		for (int Y = 0; Y < height; ++Y) {
// 			unsigned char*     LinePS = img + Y*widthstep;
// 			unsigned char*     LinePR = rCache + Y*width;
// 			for (int X = 0; X < width; ++X) {
// 				LinePR[X] = LinePS[X];
// 			}
// 		}
// 		int kernelsum = 0;
// 		for (int K = 0; K < kernelSize; K++){
// 			kernelsum += kernel[K];
// 		}
// 		float fkernelsum = 1.0f / kernelsum;
// 		for (int Y = yStart; Y < height; Y++){
// 			int heightStep = Y * width;
// 			unsigned char*     LinePR = rCache + heightStep;
// 			for (int X = xStart; X < width; X++){
// 				int cb = 0;
// 				int cg = 0;
// 				int cr = 0;
// 				for (int K = 0; K < kernelSize; K++){
// 					unsigned    int     readPos = ( (X - radius + K+width)%width);
// 					int * pmult = mult[K];
// 					cr += pmult[LinePR[readPos]];
// 				}
// 				unsigned int p = heightStep + X;
// 				r2Cache[p] = cr * fkernelsum;
// 			}
// 		}
// 		for (int X = xStart; X < width; X++){
// 			int WidthComp = X*channels;
// 			int WidthStep = width*channels;
// 			unsigned char*     LinePS = img + X*channels;
// 			unsigned char*     LinePR = r2Cache + X;
// 			for (int Y = yStart; Y < height; Y++){
// 				int cb = 0;
// 				int cg = 0;
// 				int cr = 0;
// 				for (int K = 0; K < kernelSize; K++){
// 					unsigned int   readPos = ((Y - radius + K+height)%height) * width;
// 					int * pmult = mult[K];
// 					cr += pmult[LinePR[readPos]];
// 				}
// 				int    p = Y*WidthStep;
// 				LinePS[p] = (unsigned char)(cr* fkernelsum);
// 			}
// 		}
// 		free(CacheImg);
// 	} 
// 	free(kernel);
// 	free(mult);
// }

// void GaussianSmooth(const Mat &src, Mat &dst, double sigma)
// {
// 	if(src.channels() != 1 && src.channels() != 3)
// 		return;
 
// 	//
// 	sigma = sigma > 0 ? sigma : -sigma;
// 	//高斯核矩阵的大小为(6*sigma+1)*(6*sigma+1)
// 	//ksize为奇数
// 	int ksize = ceil(sigma * 3) * 2 + 1;
 
// 	//cout << "ksize=" <<ksize<<endl;
// 	//	dst.create(src.size(), src.type());
// 	if(ksize == 1)
// 	{
// 		src.copyTo(dst);	
// 		return;
// 	}
 
// 	//计算一维高斯核
// 	double *kernel = new double[ksize];
 
// 	double scale = -0.5/(sigma*sigma);
// 	const double PI = 3.141592653;
// 	double cons = 1/sqrt(-scale / PI);
 
// 	double sum = 0;
// 	int kcenter = ksize/2;
// 	int i = 0, j = 0;
// 	for(i = 0; i < ksize; i++)
// 	{
// 		int x = i - kcenter;
// 		*(kernel+i) = cons * exp(x * x * scale);//一维高斯函数
// 		sum += *(kernel+i);
 
// //		cout << " " << *(kernel+i);
// 	}
// //	cout << endl;
// 	//归一化,确保高斯权值在[0,1]之间
// 	for(i = 0; i < ksize; i++)
// 	{
// 		*(kernel+i) /= sum;
// //		cout << " " << *(kernel+i);
// 	}
// //	cout << endl;
 
// 	dst.create(src.size(), src.type());
// 	Mat temp;
// 	temp.create(src.size(), src.type());
 
// 	uchar* srcData = src.data;
// 	uchar* dstData = dst.data;
// 	uchar* tempData = temp.data;
 
// 	//x方向一维高斯模糊
// 	for(int y = 0; y < src.rows; y++)
// 	{
// 		for(int x = 0; x < src.cols; x++)
// 		{
// 			double mul = 0;
// 			sum = 0;
// 			double bmul = 0, gmul = 0, rmul = 0;
// 			for(i = -kcenter; i <= kcenter; i++)
// 			{
// 				if((x+i) >= 0 && (x+i) < src.cols)
// 				{
// 					if(src.channels() == 1)
// 					{
// 						mul += *(srcData+y*src.step+(x+i))*(*(kernel+kcenter+i));
// 					}
// 					else 
// 					{
// 						bmul += *(srcData+y*src.step+(x+i)*src.channels() + 0)*(*(kernel+kcenter+i));
// 						gmul += *(srcData+y*src.step+(x+i)*src.channels() + 1)*(*(kernel+kcenter+i));
// 						rmul += *(srcData+y*src.step+(x+i)*src.channels() + 2)*(*(kernel+kcenter+i));
// 					}
// 					sum += (*(kernel+kcenter+i));
// 				}
// 			}
// 			if(src.channels() == 1)
// 			{
// 				*(tempData+y*temp.step+x) = mul/sum;
// 			}
// 			else
// 			{
// 				*(tempData+y*temp.step+x*temp.channels()+0) = bmul/sum;
// 				*(tempData+y*temp.step+x*temp.channels()+1) = gmul/sum;
// 				*(tempData+y*temp.step+x*temp.channels()+2) = rmul/sum;
// 			}
// 		}
// 	}
 
	
// 	//y方向一维高斯模糊
// 	for(int x = 0; x < temp.cols; x++)
// 	{
// 		for(int y = 0; y < temp.rows; y++)
// 		{
// 			double mul = 0;
// 			sum = 0;
// 			double bmul = 0, gmul = 0, rmul = 0;
// 			for(i = -kcenter; i <= kcenter; i++)
// 			{
// 				if((y+i) >= 0 && (y+i) < temp.rows)
// 				{
// 					if(temp.channels() == 1)
// 					{
// 						mul += *(tempData+(y+i)*temp.step+x)*(*(kernel+kcenter+i));
// 					}
// 					else
// 					{
// 						bmul += *(tempData+(y+i)*temp.step+x*temp.channels() + 0)*(*(kernel+kcenter+i));
// 						gmul += *(tempData+(y+i)*temp.step+x*temp.channels() + 1)*(*(kernel+kcenter+i));
// 						rmul += *(tempData+(y+i)*temp.step+x*temp.channels() + 2)*(*(kernel+kcenter+i));
// 					}
// 					sum += (*(kernel+kcenter+i));
// 				}
// 			}
// 			if(temp.channels() == 1)
// 			{
// 				*(dstData+y*dst.step+x) = mul/sum;
// 			}
// 			else
// 			{
// 				*(dstData+y*dst.step+x*dst.channels()+0) = bmul/sum;
// 				*(dstData+y*dst.step+x*dst.channels()+1) = gmul/sum;
// 				*(dstData+y*dst.step+x*dst.channels()+2) = rmul/sum;
// 			}
		
// 		}
// 	}
	
// 	delete[] kernel;
// }

/*************************************************************************
*
* 函数名称：
*   GaussSmooth2D24()
*
* 参数:
*   LPSTR lpDIBBits     - 指向源DIB图像指针
*   LONG  lWidth        - 源图像宽度（象素数）
*   LONG  lHeight       - 源图像高度（象素数）
*   float fSigma        - 方差
*
* 返回值:
*   BOOL               - 成功返回TRUE，否则返回FALSE。
*
* 说明:
*   该函数对24位位图进行高斯模糊（2维高斯模糊）。
*
************************************************************************/
#define WIDTHBYTES(bits) (((bits) + 31) / 32 * 4);
BOOL WINAPI GaussSmooth2D24(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, float fSigma)
{
    //指向高斯数据数组的指针,用作储存一维数组首元素的地址的地址
    float *fArray2D;
    // 数组的某一点到中心点的距离
    LONG iDistanceX;
    LONG iDistanceY;
    //模板高度
    int iTempH;
    //模板宽度
    int iTempW;
    //模板的中心元素X坐标 ( < iTempW - 1)
    int iTempMX;
    //模板的中心元素Y坐标 ( < iTempY - 1)
    int iTempMY;
    //π值
    double dPI = 3.1415926536;
    // 中间变量
    double  dValue;
    double  dSum = 0;
    // 数组长度，根据概率论的知识，选取[-3*sigma, 3*sigma]以内的数据。
    // 这些数据会覆盖绝大部分的滤波系数
    iTempH = 1 + 2 * ceil(3 * fSigma);   //ceil()返回大于或等于指定表达式的最小整数
    iTempW = 1 + 2 * ceil(3 * fSigma);  //ceil()返回大于或等于指定表达式的最小整数
    iTempMX = (int)iTempW / 2;
    iTempMY = (int)iTempH / 2;
    // 分配内存
    fArray2D = new float[iTempH*iTempW];
    for (int i = 0; i < iTempH; i++)
    {
        for (int j = 0; j < iTempW; j++)
        {
            iDistanceY = abs(i - (int)(iTempH / 2));
            iDistanceX = abs(j - (int)(iTempW / 2));
            double aa = -0.5 / (fSigma*fSigma);
            double bb = -aa / dPI;
            dValue = bb*exp(aa*(iDistanceX*iDistanceX + iDistanceY*iDistanceY));
            //dValue = exp(-(1 / 2)*(iDistanceX*iDistanceX + iDistanceY*iDistanceY)/ dSigma*dSigma) / (2 * dPI*dSigma*dSigma);
            (fArray2D)[i*iTempH + j] = dValue;
            dSum += dValue;
        }
    }
    // 归一化
    for (int i = 0; i < iTempH; i++)
    {
        for (int j = 0; j < iTempW; j++)
        {
            (fArray2D)[i*iTempH + j] /= dSum;
        }
    }

    // 指向源图像的指针
    unsigned char*  lpSrc;

    // 计算结果
    FLOAT   fResult1, fResult2, fResult3;

    // 图像每行的字节数
    LONG lLineBytes;

    // 计算图像每行的字节数
    lLineBytes = WIDTHBYTES(lWidth * 24);

    //定义暂时存储图像数组
    int* buf;
    buf = new int[(lHeight + iTempMY * 2) * (lWidth + iTempMX * 2) * 3];

    unsigned char* lpRed;
    unsigned char* lpGreen;
    unsigned char* lpBlue;

    //把图像复制给buf数组，并且把边缘也复制给buf数组，这样buf的大小就为(lHeight + iTempMY * 2) * (lWidth + iTempMX * 2) * 3
    for (int i = 0; i < lHeight; i++)
    {
        for (int j = 0; j < lWidth * 3; j++)
        {
            //扫描方式为从左到右，从下到上方式
            lpSrc = (unsigned char*)lpDIBBits + lLineBytes*(lHeight - 1 - i) + j;
            buf[(i + iTempMY)*(lWidth + iTempMX * 2) * 3 + iTempMX * 3 + j] = *lpSrc;
        }
    }
    //复制图像上方iTempMY*3行（1）
    for (int i = 0; i < iTempMY; i++)
    {
        for (int j = 0; j < lWidth * 3; j++)
        {
            //扫描方式为从左到右，从下到上方式
            lpSrc = (unsigned char*)lpDIBBits + lLineBytes*(lHeight - 1 - i) + j;
            buf[i*(lWidth + iTempMX * 2) * 3 + iTempMX * 3 + j] = *lpSrc;
        }
    }
    //复制图像下方iTempMY*3行（2）
    for (int i = lHeight - iTempMY; i < lHeight; i++)
    {
        for (int j = 0; j < lWidth * 3; j++)
        {
            //扫描方式为从左到右，从下到上方式
            lpSrc = (unsigned char*)lpDIBBits + lLineBytes*(lHeight - 1 - i) + j;
            buf[(iTempMY + i + iTempMY)*(lWidth + iTempMX * 2) * 3 + j + iTempMX * 3] = *lpSrc;
        }
    }
    //复制图像左方iTempMY*3列（3）
    for (int i = 0; i < lHeight; i++)
    {
        for (int j = 0; j < iTempMX * 3; j++)
        {
            //扫描方式为从左到右，从下到上方式
            lpSrc = (unsigned char*)lpDIBBits + lLineBytes*(lHeight - 1 - i) + j;
            buf[(i + iTempMY)*(lWidth + iTempMX * 2) * 3 + j] = *lpSrc;
        }
    }
    //复制图像右方iTempMY*3列（4）
    for (int i = 0; i < lHeight; i++)
    {
        for (int j = (lWidth - iTempMX) * 3; j < lWidth * 3; j++)
        {
            //扫描方式为从左到右，从下到上方式
            lpSrc = (unsigned char*)lpDIBBits + lLineBytes*(lHeight - 1 - i) + j;
            buf[(i + iTempMY)*(lWidth + iTempMX * 2) * 3 + iTempMX * 3 + j + iTempMX * 3] = *lpSrc;
        }
    }


    //复制图像左上方iTempMY*3行（1）
    for (int i = 0; i < iTempMY; i++)
    {
        for (int j = 0; j < iTempMX * 3; j++)
        {
            //扫描方式为从左到右，从下到上方式
            lpSrc = (unsigned char*)lpDIBBits + lLineBytes*(lHeight - 1 - i) + j;
            buf[i*(lWidth + iTempMX * 2) * 3 + j] = *lpSrc;
        }
    }
    //复制图像右下方iTempMY*3行（2）
    for (int i = lHeight - iTempMY; i < lHeight; i++)
    {
        for (int j = (lWidth - iTempMX) * 3; j < lWidth * 3; j++)
        {
            //扫描方式为从左到右，从下到上方式
            lpSrc = (unsigned char*)lpDIBBits + lLineBytes*(lHeight - 1 - i) + j;
            buf[(iTempMY + i + iTempMY)*(lWidth + iTempMX * 2) * 3 + iTempMX * 3 + j + iTempMX * 3] = *lpSrc;
        }
    }
    //复制图像右上方iTempMY*3行（3）
    for (int i = 0; i < iTempMY; i++)
    {
        for (int j = (lWidth - iTempMX) * 3; j < lWidth * 3; j++)
        {
            //扫描方式为从左到右，从下到上方式
            lpSrc = (unsigned char*)lpDIBBits + lLineBytes*(lHeight - 1 - i) + j;
            buf[i*(lWidth + iTempMX * 2) * 3 + iTempMX * 3 + j + iTempMX * 3] = *lpSrc;
        }
    }
    //复制图像左下方iTempMY行（4）
    for (int i = lHeight - iTempMY; i < lHeight; i++)
    {
        for (int j = 0; j < iTempMX * 3; j++)
        {
            //扫描方式为从左到右，从下到上方式
            lpSrc = (unsigned char*)lpDIBBits + lLineBytes*(lHeight - 1 - i) + j;
            buf[(iTempMY + i + iTempMY)*(lWidth + iTempMX * 2) * 3 + j] = *lpSrc;
        }
    }

    //模板运算
    for (int i = iTempMY; i < lHeight + iTempMY; i++)
    {
        for (int j = iTempMX * 3; j < (lWidth + iTempMX) * 3; j += 3)
        {
            fResult1 = 0;
            fResult2 = 0;
            fResult3 = 0;

            // 计算
            for (int k = 0; k < iTempH; k++)
            {
                for (int m = 0; m < iTempW; m++)
                {
                    //指向指针数组第i - iTempMY + k行，第j - iTempMX + m个象素的指针
                    fResult1 += buf[(i - iTempMY + k)*(lWidth + iTempMX * 2) * 3 + j + 2 - iTempMX * 3 + m * 3] * fArray2D[k * iTempW + m];
                    fResult2 += buf[(i - iTempMY + k)*(lWidth + iTempMX * 2) * 3 + j + 1 - iTempMX * 3 + m * 3] * fArray2D[k * iTempW + m];
                    fResult3 += buf[(i - iTempMY + k)*(lWidth + iTempMX * 2) * 3 + j + 0 - iTempMX * 3 + m * 3] * fArray2D[k * iTempW + m];
                }
            }

            lpRed = (unsigned char*)lpDIBBits + lLineBytes*(lHeight - 1 - i + iTempMY) + j + 2 - iTempMX * 3;
            lpGreen = (unsigned char*)lpDIBBits + lLineBytes*(lHeight - 1 - i + iTempMY) + j + 1 - iTempMX * 3;
            lpBlue = (unsigned char*)lpDIBBits + lLineBytes*(lHeight - 1 - i + iTempMY) + j + 0 - iTempMX * 3;
            // 判断是否超过255
            if (fResult1 > 255)
            {
                // 直接赋值为255
                *lpRed = 255;
            }
            else if (fResult1 < 0)
            {
                // 直接赋值为0
                *lpRed = 0;
            }
            else
            {
                // 赋值
                *lpRed = (int)fResult1;
            }

            // 判断是否超过255
            if (fResult2 > 255)
            {
                // 直接赋值为255
                *lpGreen = 255;
            }
            else if (fResult2 < 0)
            {
                // 直接赋值为0
                *lpGreen = 0;
            }
            else
            {
                // 赋值
                *lpGreen = (int)fResult2;
            }

            // 判断是否超过255
            if (fResult3 > 255)
            {
                // 直接赋值为255
                *lpBlue = 255;
            }
            else if (fResult3 < 0)
            {
                // 直接赋值为0
                *lpBlue = 0;
            }
            else
            {
                // 赋值
                *lpBlue = (int)fResult3;
            }
        }
    }
    delete[] buf;
    delete[] fArray2D;

    // 返回
    return TRUE;
}


/*************************************************************************
*
* 函数名称：
*   GaussSmooth1D24()
*
* 参数:
*   LPSTR lpDIBBits     - 指向源DIB图像指针
*   LONG  lWidth        - 源图像宽度（象素数）
*   LONG  lHeight       - 源图像高度（象素数）
*   float fSigma        - 方差
*
* 返回值:
*   BOOL               - 成功返回TRUE，否则返回FALSE。
*
* 说明:
*   该函数对24位位图进行高斯模糊（两次1维高斯模糊）。
*
************************************************************************/
BOOL WINAPI GaussSmooth1D24(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, float fSigma)
{
    //指向高斯数据数组的指针
    float *fArray1D;
    //模板的长度
    int iVectorSize;
    // 数组的中心点
    int iTemplateM;
    // 数组的某一点到中心点的距离
    int iDistance;
    //π值
    double dPI = 3.1415926536;
    // 中间变量
    double  dValue;
    double  dSum = 0;
    // 数组长度，根据概率论的知识，选取[-3*sigma, 3*sigma]以内的数据。
    // 这些数据会覆盖绝大部分的滤波系数
    iVectorSize = (int)1 + 2 * ceil(3 * fSigma);   //ceil()返回大于或等于指定表达式的最小整数
    // 中心
    iTemplateM = iVectorSize / 2;
    // 分配内存
    fArray1D = new float[iVectorSize];
    for (int i = 0; i< iVectorSize; i++)
    {
        iDistance = abs((int)(i - iTemplateM));
        double aa = -0.5 / (fSigma*fSigma);
        double bb = 1 / ((sqrt(2 * dPI))*fSigma);
        //dValue = exp(-(1 / 2)*iDistance*iDistance / (dSigma*dSigma)) / (sqrt(2 * dPI) * dSigma);
        dValue = bb*exp(aa*(iDistance*iDistance));
        (fArray1D)[i] = dValue;
        dSum += dValue;
    }
    // 归一化
    for (int i = 0; i<iVectorSize; i++)
    {
        (fArray1D)[i] /= dSum;
    }

    // 指向源图像的指针
    unsigned char*  lpSrc;

    // 计算结果
    FLOAT   fResult1, fResult2, fResult3;

    // 图像每行的字节数
    LONG lLineBytes;

    // 计算图像每行的字节数
    lLineBytes = WIDTHBYTES(lWidth * 24);

    //定义暂时存储图像数组
    int* buf;
    buf = new int[(lHeight + iTemplateM * 2) * (lWidth + iTemplateM * 2) * 3];
    // 中间变量
    int *Tmp;
    // 分配内存
    Tmp = new int[(lHeight + iTemplateM * 2) * (lWidth + iTemplateM * 2) * 3];
    //memcpy(pfTmp, buf, (lHeight + iTemplateM * 2) * (lWidth + iTemplateM * 2) * 3);

    unsigned char* lpRed;
    unsigned char* lpGreen;
    unsigned char* lpBlue;

    //把图像复制给buf数组，并且把边缘也复制给buf数组，这样buf的大小就为(lHeight + iTempMY * 2) * (lWidth + iTempMX * 2) * 3
    for (int i = 0; i < lHeight; i++)
    {
        for (int j = 0; j < lWidth * 3; j++)
        {
            //扫描方式为从左到右，从下到上方式
            lpSrc = (unsigned char*)lpDIBBits + lLineBytes*(lHeight - 1 - i) + j;
            buf[(i + iTemplateM)*(lWidth + iTemplateM * 2) * 3 + iTemplateM * 3 + j] = *lpSrc;
        }
    }

    //复制图像左方iTempMY*3列（1）
    for (int i = 0; i < lHeight; i++)
    {
        for (int j = 0; j < iTemplateM * 3; j++)
        {
            //扫描方式为从左到右，从下到上方式
            lpSrc = (unsigned char*)lpDIBBits + lLineBytes*(lHeight - 1 - i) + j;
            buf[(i + iTemplateM)*(lWidth + iTemplateM * 2) * 3 + j] = *lpSrc;
        }
    }
    //复制图像右方iTempMY*3列（2）
    for (int i = 0; i < lHeight; i++)
    {
        for (int j = (lWidth - iTemplateM) * 3; j < lWidth * 3; j++)
        {
            //扫描方式为从左到右，从下到上方式
            lpSrc = (unsigned char*)lpDIBBits + lLineBytes*(lHeight - 1 - i) + j;
            buf[(i + iTemplateM)*(lWidth + iTemplateM * 2) * 3 + iTemplateM * 3 + j + iTemplateM * 3] = *lpSrc;
        }
    }

    //把buf数组复制给pfTmp数组
    for (int i = 0; i < (lHeight + iTemplateM * 2); i++)
    {
        for (int j = 0; j < (lWidth + iTemplateM * 2) * 3; j++)
        {
            Tmp[i*(lWidth + iTemplateM * 2) * 3 + j] = buf[i*(lWidth + iTemplateM * 2) * 3 + j];
        }
    }


    //模板运算
    //先水平方向运算
    for (int i = iTemplateM; i < lHeight + iTemplateM; i++)
    {
        for (int j = iTemplateM * 3; j < (lWidth + iTemplateM) * 3; j += 3)
        {
            fResult1 = 0;
            fResult2 = 0;
            fResult3 = 0;

            // 计算
            for (int k = 0; k < iVectorSize; k++)
            {
                fResult1 += buf[i*(lWidth + iTemplateM * 2) * 3 + j + 2 - iTemplateM * 3 + k * 3] * fArray1D[k];
                fResult2 += buf[i*(lWidth + iTemplateM * 2) * 3 + j + 1 - iTemplateM * 3 + k * 3] * fArray1D[k];
                fResult3 += buf[i*(lWidth + iTemplateM * 2) * 3 + j + 0 - iTemplateM * 3 + k * 3] * fArray1D[k];
            }

            // 判断是否超过255
            if (fResult1 > 255)
            {
                // 直接赋值为255
                Tmp[i*(lWidth + iTemplateM * 2) * 3 + j + 2] = 255;
            }
            else if (fResult1 < 0)
            {
                // 直接赋值为0
                Tmp[i*(lWidth + iTemplateM * 2) * 3 + j + 2] = 0;
            }
            else
            {
                // 赋值
                Tmp[i*(lWidth + iTemplateM * 2) * 3 + j + 2] = (int)fResult1;
            }

            // 判断是否超过255
            if (fResult2 > 255)
            {
                // 直接赋值为255
                Tmp[i*(lWidth + iTemplateM * 2) * 3 + j + 1] = 255;
            }
            else if (fResult2 < 0)
            {
                // 直接赋值为0
                Tmp[i*(lWidth + iTemplateM * 2) * 3 + j + 1] = 0;
            }
            else
            {
                // 赋值
                Tmp[i*(lWidth + iTemplateM * 2) * 3 + j + 1] = (int)fResult2;
            }

            // 判断是否超过255
            if (fResult3 > 255)
            {
                // 直接赋值为255
                Tmp[i*(lWidth + iTemplateM * 2) * 3 + j + 0] = 255;
            }
            else if (fResult3 < 0)
            {
                // 直接赋值为0
                Tmp[i*(lWidth + iTemplateM * 2) * 3 + j + 0] = 0;
            }
            else
            {
                // 赋值
                Tmp[i*(lWidth + iTemplateM * 2) * 3 + j + 0] = (int)fResult3;
            }
        }
    }

    //复制图像上方iTempMY*3行（3）
    for (int i = 0; i < iTemplateM; i++)
    {
        for (int j = iTemplateM * 3; j < (lWidth + iTemplateM) * 3; j++)
        {
            Tmp[i*(lWidth + iTemplateM * 2) * 3 + j] =
                Tmp[(i + iTemplateM)*(lWidth + iTemplateM * 2) * 3 + j];
        }
    }

    //复制图像下方iTempMY*3行（4）
    for (int i = lHeight; i < lHeight + iTemplateM; i++)
    {
        for (int j = iTemplateM * 3; j < (lWidth + iTemplateM) * 3; j++)
        {
            Tmp[(i + iTemplateM)*(lWidth + iTemplateM * 2) * 3 + j] =
                Tmp[i*(lWidth + iTemplateM * 2) * 3 + j];
        }
    }


    //然后垂直方向运算
    for (int j = iTemplateM * 3; j < (lWidth + iTemplateM) * 3; j += 3)
    {
        for (int i = iTemplateM; i < lHeight + iTemplateM; i++)
        {
            fResult1 = 0;
            fResult2 = 0;
            fResult3 = 0;

            // 计算
            for (int k = 0; k < iVectorSize; k++)
            {
                fResult1 += Tmp[(i - iTemplateM + k)*(lWidth + iTemplateM * 2) * 3 + j + 2] * fArray1D[k];
                fResult2 += Tmp[(i - iTemplateM + k)*(lWidth + iTemplateM * 2) * 3 + j + 1] * fArray1D[k];
                fResult3 += Tmp[(i - iTemplateM + k)*(lWidth + iTemplateM * 2) * 3 + j + 0] * fArray1D[k];
            }

            lpRed = (unsigned char*)lpDIBBits + lLineBytes*(lHeight - 1 - i + iTemplateM) + j + 2 - iTemplateM * 3;
            lpGreen = (unsigned char*)lpDIBBits + lLineBytes*(lHeight - 1 - i + iTemplateM) + j + 1 - iTemplateM * 3;
            lpBlue = (unsigned char*)lpDIBBits + lLineBytes*(lHeight - 1 - i + iTemplateM) + j + 0 - iTemplateM * 3;

            // 判断是否超过255
            if (fResult1 > 255)
            {
                // 直接赋值为255
                *lpRed = 255;
            }
            else if (fResult1 < 0)
            {
                // 直接赋值为0
                *lpRed = 0;
            }
            else
            {
                // 赋值
                *lpRed = (int)fResult1;
            }

            // 判断是否超过255
            if (fResult2 > 255)
            {
                // 直接赋值为255
                *lpGreen = 255;
            }
            else if (fResult2 < 0)
            {
                // 直接赋值为0
                *lpGreen = 0;
            }
            else
            {
                // 赋值
                *lpGreen = (int)fResult2;
            }

            // 判断是否超过255
            if (fResult3 > 255)
            {
                // 直接赋值为255
                *lpBlue = 255;
            }
            else if (fResult3 < 0)
            {
                // 直接赋值为0
                *lpBlue = 0;
            }
            else
            {
                // 赋值
                *lpBlue = (int)fResult3;
            }
        }
    }

    delete[] buf;
    delete[] Tmp;
    delete[] fArray1D;

    // 返回
    return TRUE;
}