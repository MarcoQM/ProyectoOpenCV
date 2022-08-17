#include <iostream>
#include <fstream>
#include<vector>

#include "Image.h"
#include "RGB.h"


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
            std::cout<<static_cast<float>(imagen[i][j])<<" ";
        }
        std::cout<<std::endl;
    }
}

template<typename PixelType>
DataType<PixelType> paddingConstantValue(DataType<PixelType>& imagen, unsigned paddingSize, float value = 0)
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
DataType<PixelType> convolution(DataType<PixelType>& imagen, DataType<float> kernel, float scale, std::string padding, unsigned valuePadding = 0)
{
    std::size_t Rows = imagen.size();
    std::size_t Columns = imagen[0].size();

    DataType<PixelType> imagePadding;
    DataType<PixelType> result = DataType<PixelType>(Rows, std::vector<PixelType>(Columns, PixelType{0}));

    //Tamanio del padding
    unsigned paddingSize = kernel.size()/2;

    //Padding selection
    // Padding: constant, expanded, mirror, repetition
    imagePadding = paddingMirror(imagen, paddingSize);
    if(padding == "constant")
    {imagePadding = paddingConstantValue(imagen, paddingSize, valuePadding);}
    else if(padding == "expanded")
    {imagePadding = paddingExpanded(imagen, paddingSize);}
    else if(padding == "mirror")
    {imagePadding = paddingMirror(imagen, paddingSize);}
    else if(padding == "repetition")
    {imagePadding = paddingPeriodicRepetitions(imagen, paddingSize);}

    for(unsigned i = 0; i < Rows; ++i)
    {
        for(unsigned j = 0; j < Columns; ++j)
        {
            //PixelType m{0};
            float m = 0;
            //for para el kernel
            for(unsigned h = 0; h < kernel.size(); ++h)
            {
                for(unsigned k = 0; k < kernel[h].size(); ++k)
                {
                    m = m + ((imagePadding[h+i][k+j] * kernel[h][k]) / scale);
                }

            }
            result[i][j] = m;
            //std::cout<<m<<std::endl;
        }
    }

    return result;
}

template<typename PixelType>
DataType<PixelType> findContoursHC(DataType<PixelType>& image)
{

    //image2.SetData(convolution(image.GetData(), kernel7, 9, "expanded"));

   // Operador de sobel segund derivada
    std::vector<std::vector<float>> Hsx = {{-1, 0, 1},
                                                {-2, 0, 2},
                                                {-1, 0, 1}};

    std::vector<std::vector<float>> Hsy = {{-1, -2, -1},
                                                {0, 0, 0},
                                                {1, 2, 1}};

    // Padding: constant, expanded, mirror, repetition
    DataType<PixelType> resHsx = convolution(image, Hsx, 6, "repetition");
    DataType<PixelType> resHsy = convolution(image, Hsy, 6, "repetition");


    // Encontrando la tangente
    std::size_t Rows = image.size();
    std::size_t Columns = image[0].size();


    DataType<PixelType> result = DataType<PixelType>(Rows, std::vector<PixelType>(Columns, PixelType{0}));

    for(unsigned i = 0; i < Rows; ++i)
    {
        for(unsigned j = 0; j < Columns; ++j)
        {
            result[i][j] = std::sqrt(std::pow(resHsx[i][j],2) + std::pow(resHsy[i][j],2));
        }
    }

    return result;
}

template<typename PixelType>
DataType<PixelType> findDirectionsHC(DataType<PixelType>& image)
{

    //image2.SetData(convolution(image.GetData(), kernel7, 9, "expanded"));

   // Operador de sobel segund derivada
    std::vector<std::vector<float>> Hsx = {{-1, 0, 1},
                                                {-2, 0, 2},
                                                {-1, 0, 1}};

    std::vector<std::vector<float>> Hsy = {{-1, -2, -1},
                                                {0, 0, 0},
                                                {1, 2, 1}};

    // Padding: constant, expanded, mirror, repetition
    DataType<PixelType> resHsx = convolution(image, Hsx, 6, "repetition");
    DataType<PixelType> resHsy = convolution(image, Hsy, 6, "repetition");


    // Encontrando la tangente
    std::size_t Rows = image.size();
    std::size_t Columns = image[0].size();


    DataType<PixelType> result = DataType<PixelType>(Rows, std::vector<PixelType>(Columns, PixelType{0}));

    for(unsigned i = 0; i < Rows; ++i)
    {
        for(unsigned j = 0; j < Columns; ++j)
        {
            //result[i][j] = std::sqrt(std::pow(resHsx[i][j],2) + std::pow(resHsy[i][j],2));
            // Se convierte a grados
            result[i][j] = atan(resHsy[i][j] / resHsx[i][j])*57.2958;
        }
    }

    return result;
}

void generateFileCSVGradient()
{
    std::string directory = "/home/marco/ProyectosQt/OpenCV_Example";
    std::string directoryImages = "/home/marco/ProyectosQt/fire_dataset";

    std::string fileNameFire  = directory+"/fireGradient.csv"; //Creacion del archivo csv
    std::ofstream frame (fileNameFire);
    if (!frame.is_open())
    {
        std::cerr<<"Error opening "<<fileNameFire <<std::endl;
        return;
    }


    //Images fire
    for(unsigned i = 1; i < 756; ++i)
    {
        Image<float> imageFire;
        imageFire.Read(directoryImages + "/fire_images/fire." + std::to_string(i)+ ".png");
        auto temp = findContoursHC(imageFire.GetData());
        for(unsigned j = 0; j < temp.size(); ++j)
            for(unsigned h = 0; h < temp[j].size(); ++h)
                (h != temp[j].size() - 1) ? frame <<temp[j][h]<<"; " : frame <<temp[j][h];
        frame <<std::endl;

    }


    std::string fileNameNonFire  = directory+"/nonFireGradient.csv"; //Creacion del archivo csv
    std::ofstream frame2 (fileNameNonFire);
    if (!frame2.is_open())
    {
        std::cerr<<"Error opening "<<fileNameNonFire <<std::endl;
        return;
    }

    //Images non fire
    for(unsigned i = 1; i < 245; ++i)
    {
        Image<float> imageNonFire;
        imageNonFire.Read(directoryImages + "/non_fire_images/non_fire." + std::to_string(i)+ ".png");
        auto temp = findContoursHC(imageNonFire.GetData());
        for(unsigned j = 0; j < temp.size(); ++j)
            for(unsigned h = 0; h < temp[j].size(); ++h)
                (h != temp[j].size() - 1) ? frame2 <<temp[j][h]<<"; " : frame2 <<temp[j][h];
        frame2 <<std::endl;
    }
}

void generateFileCSVHistrogram()
{
    std::string directory = "/home/marco/ProyectosQt/OpenCV_Example";
    std::string directoryImages = "/home/marco/ProyectosQt/fire_dataset";

    std::string fileNameFire  = directory+"/fireHistogram.csv"; //Creacion del archivo csv
    std::ofstream frame (fileNameFire);
    if (!frame.is_open())
    {
        std::cerr<<"Error opening "<<fileNameFire <<std::endl;
        return;
    }


    //Images fire
    for(unsigned i = 1; i < 756; ++i)
    {
        Image<uchar> imageFire;
        imageFire.Read(directoryImages + "/fire_images/fire." + std::to_string(i)+ ".png");


        // Se podria aplicar un kernel
        auto temp = imageFire.Histogram();
        for(unsigned j = 0; j < temp.size(); ++j)
            for(unsigned h = 0; h < temp[j].size(); ++h)
                (h != temp[j].size() - 1) ? frame <<temp[j][h]<<"; " : frame <<temp[j][h];
        frame <<std::endl;
    }


    std::string fileNameNonFire  = directory+"/nonFireHistrogram.csv"; //Creacion del archivo csv
    std::ofstream frame2 (fileNameNonFire);
    if (!frame2.is_open())
    {
        std::cerr<<"Error opening "<<fileNameNonFire <<std::endl;
        return;
    }

    //Images non fire
    for(unsigned i = 1; i < 245; ++i)
    {
        Image<uchar> imageNonFire;
        imageNonFire.Read(directoryImages + "/non_fire_images/non_fire." + std::to_string(i)+ ".png");
        // Se podria aplicar un kernel
        auto temp = imageNonFire.Histogram();
        for(unsigned j = 0; j < temp.size(); ++j)
            for(unsigned h = 0; h < temp[j].size(); ++h)
                (h != temp[j].size() - 1) ? frame2 <<temp[j][h]<<"; " : frame2 <<temp[j][h];
        frame2 <<std::endl;
    }
}


int main()
{
    //Image<float> image;
    //image.Read("/home/marco/ProyectosQt/OpenCV_Example/image.jpg");
    //image.Read("/home/marco/ProyectosQt/fire_dataset/fire_images/fire.32.png");
    //image.Show();

    // Padding: constant, expanded, mirror, repetition
    //Image<float> image2;


    //image2.SetData(findContoursHC(image.GetData()));
    //image2.Show();
    //image2.SetData(findDirectionsHC(image.GetData()));
    //image2.Show();

    //generateFileCSVGradient();
    generateFileCSVHistrogram();







    return 0;
}
