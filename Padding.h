#ifndef PADDING_H
#define PADDING_H

#include <vector>
#include <string>

template<typename PixelType> //uchar->intensity, vector<uchar> rgb
class Padding
{
public:
    Padding(){};

    std::vector<std::vector<PixelType>> paddingConstantvalue(std::vector<std::vector<PixelType>>& imagen, unsigned paddingSize);
    std::vector<std::vector<PixelType>> paddingMirror(std::vector<std::vector<PixelType>>& imagen, unsigned paddingSize);
    std::vector<std::vector<PixelType>> paddingExpanded(std::vector<std::vector<PixelType>>& imagen, unsigned paddingSize);
    std::vector<std::vector<PixelType>> paddingPeriodicRepetitions(std::vector<std::vector<PixelType>>& imagen, unsigned paddingSize);
};

template<typename PixelType>
std::vector<std::vector<PixelType>> paddingConstantvalue(std::vector<std::vector<PixelType>>& imagen, unsigned paddingSize)
{
    std::size_t Rows = imagen.size();
    std::size_t Columns = imagen[0].size();

    std::size_t paddingRows = imagen.size() + 2*paddingSize;
    std::size_t paddingColumns = imagen[0].size() + 2*paddingSize;

    std::vector<std::vector<unsigned>> paddedImage = std::vector<std::vector<PixelType>>(paddingRows, std::vector<PixelType>(paddingColumns, 0));

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
std::vector<std::vector<PixelType>> paddingMirror(std::vector<std::vector<PixelType>>& imagen, unsigned paddingSize)
{
    std::size_t Rows = imagen.size();
    std::size_t Columns = imagen[0].size();

    std::size_t paddingRows = Rows + 2*paddingSize;
    std::size_t paddingColumns = Columns + 2*paddingSize;

    std::vector<std::vector<unsigned>> paddedImage = std::vector<std::vector<PixelType>>(paddingRows, std::vector<PixelType>(paddingColumns, 0));

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
std::vector<std::vector<PixelType>> paddingExpanded(std::vector<std::vector<PixelType>>& imagen, unsigned paddingSize)
{
    std::size_t Rows = imagen.size();
    std::size_t Columns = imagen[0].size();

    std::size_t paddingRows = Rows + 2*paddingSize;
    std::size_t paddingColumns = Columns + 2*paddingSize;

    std::vector<std::vector<unsigned>> paddedImage = std::vector<std::vector<PixelType>>(paddingRows, std::vector<PixelType>(paddingColumns, 0));

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
std::vector<std::vector<PixelType>> paddingPeriodicRepetitions(std::vector<std::vector<PixelType>>& imagen, unsigned paddingSize)
{
    std::size_t Rows = imagen.size();
    std::size_t Columns = imagen[0].size();

    std::size_t paddingRows = Rows + 2*paddingSize;
    std::size_t paddingColumns = Columns + 2*paddingSize;

    std::vector<std::vector<unsigned>> paddedImage = std::vector<std::vector<PixelType>>(paddingRows, std::vector<PixelType>(paddingColumns, 0));

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




#endif // PADDING_H
