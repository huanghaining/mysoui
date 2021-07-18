#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <iostream>
#include <fstream>

#define NOMINMAX
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

typedef struct
{
    uint8_t r, g, b, a;
} rgb32;


#if !defined(_WIN32) && !defined(_WIN64)
#pragma pack(2)
typedef struct
{
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} BITMAPFILEHEADER;
#pragma pack()


#pragma pack(2)
typedef struct
{
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int16_t biXPelsPerMeter;
    int16_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} BITMAPINFOHEADER;
#pragma pack()
#endif

#pragma pack(2)
typedef struct
{
    BITMAPFILEHEADER bfh;
    BITMAPINFOHEADER bih;
} BMPINFO;
#pragma pack()


class bitmap
{
private:
    BMPINFO bmpInfo;
    uint8_t* pixels;

public:
    bitmap(const char* path);
    ~bitmap();

    void save(const char* path, uint16_t bit_count = 24);

    rgb32* getPixel(uint32_t x, uint32_t y) const;
    void setPixel(rgb32* pixel, uint32_t x, uint32_t y);

    uint32_t getWidth() const;
    uint32_t getHeight() const;
    uint16_t bitCount() const;
};

bitmap::bitmap(const char* path) : bmpInfo(), pixels(nullptr)
{
    std::ifstream file(path, std::ios::in | std::ios::binary);

    if (file)
    {
        file.read(reinterpret_cast<char*>(&bmpInfo.bfh), sizeof(bmpInfo.bfh));

        if (bmpInfo.bfh.bfType != 0x4d42)
        {
            throw std::runtime_error("Invalid format. Only bitmaps are supported.");
        }

        file.read(reinterpret_cast<char*>(&bmpInfo.bih), sizeof(bmpInfo.bih));

		/*  if (bmpInfo.bih.biCompression != 0)
		  {
		  std::cerr << bmpInfo.bih.biCompression << "\n";
		  throw std::runtime_error("Invalid bitmap. Only uncompressed bitmaps are supported.");
		  }

		  if (bmpInfo.bih.biBitCount != 24 && bmpInfo.bih.biBitCount != 32)
		  {
		  throw std::runtime_error("Invalid bitmap. Only 24bit and 32bit bitmaps are supported.");
		  }*/

        file.seekg(bmpInfo.bfh.bfOffBits, std::ios::beg);

        pixels = new uint8_t[bmpInfo.bfh.bfSize - bmpInfo.bfh.bfOffBits];
        file.read(reinterpret_cast<char*>(&pixels[0]), bmpInfo.bfh.bfSize - bmpInfo.bfh.bfOffBits);


        uint8_t* temp = new uint8_t[bmpInfo.bih.biWidth * bmpInfo.bih.biHeight * sizeof(rgb32)];

        uint8_t* in = pixels;
        rgb32* out = reinterpret_cast<rgb32*>(temp);
        int padding = bmpInfo.bih.biBitCount == 24 ? ((bmpInfo.bih.biSizeImage - bmpInfo.bih.biWidth * bmpInfo.bih.biHeight * 3) / bmpInfo.bih.biHeight) : 0;

        for (int i = 0; i < bmpInfo.bih.biHeight; ++i, in += padding)
        {
            for (int j = 0; j < bmpInfo.bih.biWidth; ++j)
            {

                out->b = *(in++);
                out->g = *(in++);
                out->r = *(in++);
                out->a = bmpInfo.bih.biBitCount == 32 ? *(in++) : 0xFF;
                ++out;
            }
        }

        delete[] pixels;
        pixels = temp;
    }
}

bitmap::~bitmap()
{
    delete[] pixels;
}

void bitmap::save(const char* path, uint16_t bit_count)
{
    std::ofstream file(path, std::ios::out | std::ios::binary);

    if (file)
    {
        bmpInfo.bih.biBitCount = bit_count;
        uint32_t size = ((bmpInfo.bih.biWidth * bmpInfo.bih.biBitCount + 31) / 32) * 4 * bmpInfo.bih.biHeight;
        bmpInfo.bfh.bfSize = bmpInfo.bfh.bfOffBits + size;

        file.write(reinterpret_cast<char*>(&bmpInfo.bfh), sizeof(bmpInfo.bfh));
        file.write(reinterpret_cast<char*>(&bmpInfo.bih), sizeof(bmpInfo.bih));
        file.seekp(bmpInfo.bfh.bfOffBits, std::ios::beg);

        uint8_t* out = NULL;
        rgb32* in = reinterpret_cast<rgb32*>(pixels);
        uint8_t* temp = out = new uint8_t[bmpInfo.bih.biWidth * bmpInfo.bih.biHeight * sizeof(rgb32)];
        int padding = bmpInfo.bih.biBitCount == 24 ? ((bmpInfo.bih.biSizeImage - bmpInfo.bih.biWidth * bmpInfo.bih.biHeight * 3) / bmpInfo.bih.biHeight) : 0;

        for (int i = 0; i < bmpInfo.bih.biHeight; ++i, out += padding)
        {
            for (int j = 0; j < bmpInfo.bih.biWidth; ++j)
            {
                *(out++) = in->b;
                *(out++) = in->g;
                *(out++) = in->r;

                if (bmpInfo.bih.biBitCount == 32)
                {
                    *(out++) = in->a;
                }
                ++in;
            }
        }

        file.write(reinterpret_cast<char*>(&temp[0]), size); //bmpInfo.bfh.bfSize - bmpInfo.bfh.bfOffBits
        delete[] temp;
    }
}

rgb32* bitmap::getPixel(uint32_t x, uint32_t y) const
{
    rgb32* temp = reinterpret_cast<rgb32*>(pixels);
    return &temp[(bmpInfo.bih.biHeight - 1 - y) * bmpInfo.bih.biWidth + x];
}

void bitmap::setPixel(rgb32* pixel, uint32_t x, uint32_t y)
{
    rgb32* temp = reinterpret_cast<rgb32*>(pixels);
    memcpy(&temp[(bmpInfo.bih.biHeight - 1 - y) * bmpInfo.bih.biWidth + x], pixel, sizeof(rgb32));
};

uint32_t bitmap::getWidth() const
{
    return bmpInfo.bih.biWidth;
}

uint32_t bitmap::getHeight() const
{
    return bmpInfo.bih.biHeight;
}

uint16_t bitmap::bitCount() const
{
    return bmpInfo.bih.biBitCount;
}

void apply_blur(int x, int y, bitmap* bmp, int blurRadius)
{
    double blurValue = 0.111;
    int r = 0;
    int g = 0;
    int b = 0;

    for (int k = y - blurRadius; k <= blurRadius; ++k)
    {
        for (int l = x - blurRadius; l <= blurRadius; ++l)
        {
            rgb32* pixel = bmp->getPixel(l, k);
            r += blurValue * pixel->r;
            g += blurValue * pixel->g;
            b += blurValue * pixel->b;
        }
    }

    rgb32 pixel = *bmp->getPixel(x, y);

    pixel.r = r;
    pixel.g = g;
    pixel.b = b;

    bmp->setPixel(&pixel, x, y);
}
void blur(bitmap* bmp, int radius);



void blur(bitmap* bmp, int radius)
{
    float rs = ceil(radius * 2.57);
    for (int i = 0; i < bmp->getHeight(); ++i)
    {
        for (int j = 0; j < bmp->getWidth(); ++j)
        {
            double r = 0, g = 0, b = 0;
            double count = 0;

            for (int iy = i - rs; iy < i + rs + 1; ++iy)
            {
                for (int ix = j - rs; ix < j + rs + 1; ++ix)
                {
                    auto x = min(static_cast<int>(bmp->getWidth()) - 1, max(0, ix));
                    auto y = min(static_cast<int>(bmp->getHeight()) - 1, max(0, iy));

                    auto dsq = ((ix - j) * (ix - j)) + ((iy - i) * (iy - i));
                    auto wght = std::exp(-dsq / (2.0 * radius * radius)) / (M_PI * 2.0 * radius * radius);

                    rgb32* pixel = bmp->getPixel(x, y);

                    r += pixel->r * wght;
                    g += pixel->g * wght;
                    b += pixel->b * wght;
                    count += wght;
                }
            }

            rgb32* pixel = bmp->getPixel(j, i);
            pixel->r = std::round(r / count);
            pixel->g = std::round(g / count);
            pixel->b = std::round(b / count);
        }
    }
}

// int main(int argc, const char* argv[])
// {
//     bitmap bmp{ "C:\\Users\\strives\\Desktop\\new_2.bmp" };
//     blur(&bmp, 5);
//     bmp.save("C:\\Users\\strives\\Desktop\\blurred-panda.bmp");
//     return 0;
// }