#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>

#include <opencv2/opencv.hpp>

template<typename PixelType> //uchar->intensity, vector<uchar> rgb
class Image
{

    using DataType = std::vector<std::vector<PixelType>>; //matrix

public:
    Image(){};

    void Read(const std::string& fileName);

private:

    DataType Data; // matriz de pixels

    std::size_t Rows{};
    std::size_t Columns{};

};





template<typename  PixelType>
void Image<PixelType>::Read(const std::string& fileName)
{

    cv::Mat image = cv::imread(fileName, cv::IMREAD_COLOR);

    if (!image.data)
    {
        std::cerr<<"No image data\n";
        return;
    }

    Rows = image.rows;
    Columns = image.cols;

    Data = DataType(Rows, std::vector<PixelType>(Columns, PixelType{}));

    uchar red, green, blue;
    for (unsigned r=0; r < Rows; ++r)
    {
        cv::Vec3b * row = image.ptr<cv::Vec3b>(r);
        for (unsigned c=0; c < Columns; ++c)
        {
            red =   row[c][2]; //B
            green = row[c][1]; //G
            blue =  row[c][0]; //R

            if constexpr (std::is_fundamental<PixelType>::value) //uchar, short, float (gray)
            {
                Data[r][c] = static_cast<PixelType>((red + green + blue)/3);
            }
            else //RGB LAB, channels...
            {
                //memoria
                Data[r][c][0] = static_cast<typename PixelType::ValueType>(red);
                Data[r][c][1] = static_cast<typename PixelType::ValueType>(green);
                Data[r][c][2] = static_cast<typename PixelType::ValueType>(blue);
            }


        }
    }

    std::cout<<image.ptr<cv::Vec3b>(0)[0]<<"\n";
    //std::cout<<+Data[0][0][0]<<","<<+Data[0][0][1]<<","<<+Data[0][0][2]<<"\n";


    cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Image", image);
    cv::waitKey(0);

}




#endif // IMAGE_H
