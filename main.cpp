#include <iostream>
#include "Image.h"
#include "RGB.h"
#include<vector>

template<typename PixelType>
using DataType = std::vector<std::vector<PixelType>>;

template<typename PixelType>
void imprimir(DataType<PixelType> imagen)
{
    for(unsigned i = 0; i < imagen.size(); ++i)
    {
        for(unsigned j = 0; j < imagen[i].size(); ++j)
        {
            std::cout<<imagen[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

template<typename PixelType>
DataType<PixelType> paddingConstantvalue(DataType<PixelType>& imagen, unsigned paddingSize, uchar value = 0)
{
    std::size_t Rows = imagen.size();
    std::size_t Columns = imagen[0].size();

    std::size_t paddingRows = imagen.size() + 2*paddingSize;
    std::size_t paddingColumns = imagen[0].size() + 2*paddingSize;

    DataType<PixelType> paddedImage = DataType<PixelType>(paddingRows, std::vector<PixelType>(paddingColumns, PixelType{value}));

    for(unsigned i = 0; i < Rows; ++i)
    {
        for(unsigned j = 0; j < Columns; ++j)
        {
            paddedImage[i+paddingSize][j+paddingSize] = imagen[i][j];
        }
    }
    return paddedImage;
}

template<typename PixelType>
DataType<PixelType> paddingMirror(DataType<PixelType>& imagen, unsigned paddingSize)
{
    std::size_t Rows = imagen.size();
    std::size_t Columns = imagen[0].size();

    std::size_t paddingRows = Rows + 2*paddingSize;
    std::size_t paddingColumns = Columns + 2*paddingSize;

    DataType<PixelType> paddedImage = DataType<PixelType>(paddingRows, std::vector<PixelType>(paddingColumns, PixelType{0}));

    for(unsigned i = 0; i < Rows; ++i)
    {
        for(unsigned j = 0; j < Columns; ++j)
        {
            paddedImage[i+paddingSize][j+paddingSize] = imagen[i][j];
        }
    }

    unsigned distanceMirror = 1;

    //top padding
    distanceMirror = 1;
    for(unsigned i = paddingSize; i > 0; --i)
    {

        for(unsigned j = paddingSize; j < Columns+paddingSize; ++j)
        {
            paddedImage[i-1][j] = paddedImage[i+distanceMirror-1][j];
        }
        distanceMirror+=2;
    }

    //bottom padding
    distanceMirror = 1;
    for(unsigned i = paddingRows-paddingSize; i < paddingRows; ++i)
    {
        for(unsigned j = paddingSize; j < Columns+paddingSize; ++j)
        {
            paddedImage[i][j] = paddedImage[i-distanceMirror][j];
        }
        distanceMirror+=2;
    }

    //left padding
    distanceMirror = 1;
    for(unsigned j = paddingSize; j > 0; --j)
    {
        for(unsigned i = 0; i < paddingRows; ++i)
        {
             //std::cout<<i<<","<<j+distanceMirror-1<<std::endl;
             paddedImage[i][j-1] = paddedImage[i][j+distanceMirror-1];
        }
        distanceMirror+=2;
    }

    // right padding
    distanceMirror = 1;
    for(unsigned j = paddingColumns - paddingSize; j < paddingColumns; ++j)
    {
        for(unsigned i = 0; i < paddingRows; ++i)
        {
             paddedImage[i][j] = paddedImage[i][j-distanceMirror];
        }
        distanceMirror+=2;
    }

    return paddedImage;
}

template<typename PixelType>
DataType<PixelType> paddingExpanded(DataType<PixelType>& imagen, unsigned paddingSize)
{
    std::size_t Rows = imagen.size();
    std::size_t Columns = imagen[0].size();

    std::size_t paddingRows = Rows + 2*paddingSize;
    std::size_t paddingColumns = Columns + 2*paddingSize;

    DataType<PixelType> paddedImage = DataType<PixelType>(paddingRows, std::vector<PixelType>(paddingColumns, PixelType{0}));

    for(unsigned i = 0; i < Rows; ++i)
    {
        for(unsigned j = 0; j < Columns; ++j)
        {
            paddedImage[i+paddingSize][j+paddingSize] = imagen[i][j];
        }
    }

    //top padding
    for(unsigned i = paddingSize; i > 0; --i)
    {

        for(unsigned j = paddingSize; j < Columns+paddingSize; ++j)
        {
            paddedImage[i-1][j] = paddedImage[i][j];
        }
    }

    //bottom padding
    for(unsigned i = paddingRows-paddingSize; i < paddingRows; ++i)
    {
        for(unsigned j = paddingSize; j < Columns+paddingSize; ++j)
        {
            paddedImage[i][j] = paddedImage[i-1][j];
        }
    }

    //left padding
    for(unsigned j = paddingSize; j > 0; --j)
    {
        for(unsigned i = 0; i < paddingRows; ++i)
        {
             paddedImage[i][j-1] = paddedImage[i][j];
        }
    }

    // right padding
    for(unsigned j = paddingColumns - paddingSize; j < paddingColumns; ++j)
    {
        for(unsigned i = 0; i < paddingRows; ++i)
        {
             paddedImage[i][j] = paddedImage[i][j-1];
        }
    }
    return paddedImage;
}

template<typename PixelType>
DataType<PixelType> paddingPeriodicRepetitions(DataType<PixelType>& imagen, unsigned paddingSize)
{
    std::size_t Rows = imagen.size();
    std::size_t Columns = imagen[0].size();

    std::size_t paddingRows = Rows + 2*paddingSize;
    std::size_t paddingColumns = Columns + 2*paddingSize;

    DataType<PixelType> paddedImage = DataType<PixelType>(paddingRows, std::vector<PixelType>(paddingColumns, PixelType{0}));

    for(unsigned i = 0; i < Rows; ++i)
    {
        for(unsigned j = 0; j < Columns; ++j)
        {
            paddedImage[i+paddingSize][j+paddingSize] = imagen[i][j];
        }
    }

    //top padding
    for(unsigned i = 0; i < paddingSize; ++i)
    {
        for(unsigned j = paddingSize; j < Columns+paddingSize; ++j)
        {
            paddedImage[i][j] = paddedImage[i+Rows][j];
        }
    }

    //bottom padding
    for(unsigned i = paddingRows-paddingSize; i < paddingRows; ++i)
    {
        for(unsigned j = paddingSize; j < Columns+paddingSize; ++j)
        {
            paddedImage[i][j] = paddedImage[i-Rows][j];
        }
    }

    //left padding
    for(unsigned j = 0; j < paddingSize; ++j)
    {
        for(unsigned i = 0; i < paddingRows; ++i)
        {
             paddedImage[i][j] = paddedImage[i][j+Columns];
        }
    }

    // right padding
    for(unsigned j = paddingColumns - paddingSize; j < paddingColumns; ++j)
    {
        for(unsigned i = 0; i < paddingRows; ++i)
        {
             paddedImage[i][j] = paddedImage[i][j-Columns];
        }
    }

    return paddedImage;
}

template<typename PixelType>
void convolution(Image<PixelType> image)
{

}




int main()
{

    Image<RGB<uchar>> image;
    image.Read("/home/marco/ProyectosQt/OpenCV_Example/image.jpg");
    image.Show();

    imprimir(paddingMirror(image.GetData(), 2));


    /*std::vector<std::vector<unsigned>> imagen = {{1, 2, 3},
                                                 {4, 5, 6},
                                                 {7, 8, 9}};*/

    /*imagen = {{1, 2, 3, 4, 5},
              {2, 3, 4, 5, 6},
              {3, 4, 5, 6, 7},
              {4, 5, 6, 7, 8}};*/

    //paddingConstantvalue(imagen, 1);


    //imprimir(paddingConstantvalue(imagen, 2, 6));
    //imprimir(paddingConstantvalue(imagen, 2, 7));


    return 0;
}
