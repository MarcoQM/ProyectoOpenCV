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
            //std::cout<<imagen[i][j]<<" ";
            std::cout<<static_cast<int>(imagen[i][j])<<" ";
        }
        std::cout<<std::endl;
    }
}

template<typename PixelType>
DataType<PixelType> paddingConstantValue(DataType<PixelType>& imagen, unsigned paddingSize, uchar value = 0)
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

// Padding, Kernel K, Factor de scala S, padding, valor de padding(solo caso1)
template<typename PixelType>
DataType<PixelType> convolution(DataType<PixelType>& imagen, DataType<float> kernel, int scale, std::string padding, unsigned valuePadding = 0)
{
    std::size_t Rows = imagen.size();
    std::size_t Columns = imagen[0].size();

    DataType<PixelType> imagePadding;
    DataType<PixelType> result = DataType<PixelType>(Rows, std::vector<PixelType>(Columns, PixelType{0}));

    //Tamanio del padding
    unsigned paddingSize = kernel.size()/2;

    //Padding selection
    imagePadding = paddingMirror(imagen, paddingSize);

    for(unsigned i = 0; i < Rows; ++i)
    {
        for(unsigned j = 0; j < Columns; ++j)
        {
            float m=0;
            //for para el kernel
            for(unsigned h = 0; h < kernel.size(); ++h)
            {
                for(unsigned k = 0; k < kernel[h].size(); ++k)
                {
                    m = m + imagePadding[h+i][k+j] * kernel[h][k];
                }

            }
            result[i][j] = m/scale;
        }
    }

    return result;
}




int main()
{

    Image<uchar> image;
    image.Read("/home/marco/ProyectosQt/OpenCV_Example/image.jpg");
    //image.Show();


    std::vector<std::vector<float>> kernel = {{1, 1, 1},
                                              {1, 1, 1},
                                              {1, 1, 1}};

    std::vector<std::vector<float>> kernel2 = {{0, 0, 0, 0, 0},
                                               {0, 1, 1, 1, 0},
                                               {0, 1, 1, 1, 0},
                                               {0, 1, 1, 1, 0},
                                               {0, 0, 0, 0, 0}};

    std::vector<std::vector<float>> kernel3 = {{0, 1, 2, 1, 0},
                                               {1, 3, 5, 3, 1},
                                               {2, 5, 9, 5, 2},
                                               {1, 3, 5, 3, 1},
                                               {0, 1, 2, 1, 0}};

    std::vector<std::vector<float>> kernel4 = {{0, 0, -1, 0, 0},
                                               {0, -1, -2, -1, 0},
                                               {-1, -2, 16, -2, -1},
                                               {0, -1, -2, -1, 0},
                                               {0, 0, -1, 0, 0}};

    std::vector<std::vector<float>> kernel5 = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                               {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                               {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                               {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                               {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                               {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                               {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                               {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                               {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                               {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

    std::vector<std::vector<float>> kernel6 = {{0, 1, 0},
                                               {1, -4, 1},
                                               {0, 1, 0}};

    std::vector<std::vector<float>> kernel7 = {{-2, -1, 0},
                                               {-1, 1, 1},
                                               {0, 1, 2}};

    std::vector<std::vector<uchar>> test = {{1, 2, 3},
                                            {4, 5, 6},
                                            {7, 8, 9}};

    // Padding: Constant, Expanded, Mirror, Repetition
    //convolution(image.GetData(), kernel, 9, "Constant");
    Image<uchar> image2;
    image2.SetData(convolution(image.GetData(), kernel7, 9, "Constant"));
    //image2.SetData(convolution(test, kernel, 9, "Constant"));
    image2.Show();
    //imprimir(convolution(image.GetData(), kernel, 9, "Constant"));


    /*Image<uchar> image2;
    image2.SetData(paddingConstantValue(image.GetData(), 100));
    image2.Show();*/

    //imprimir(paddingMirror(image.GetData(), 2));





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
