#include <iostream>
#include "Image.h"
#include "RGB.h"

#include<vector>

int main()
{

    /*Image< RGB<uchar> > image;
    image.Read("/home/marco/ProyectosQt/OpenCV_Example/image.jpg");
    image.Show();
    auto histogram = image.Histogram();


    //std::cout<<histogram.size()<<std::endl;
    for(unsigned i = 0; i < histogram.size(); ++i)
    {
        std::cout<<std::endl<<"Canal #"<<i<<std::endl;
        for(unsigned j = 0; j < histogram[i].size(); ++j)
        {
            std::cout<<j<<" -> "<<histogram[i][j]<<std::endl;
        }
    }*/
    RGB<uchar> color;
    color[0] = 255;
    color[1] = 6;
    color[2] = 20;

    RGB<uchar> color2;
    color2[0] = 100;
    color2[1] = 10;
    color2[2] = 10;

    std::cout<<static_cast<int>(color[0])<<"-"<<static_cast<int>(color[1])<<"-"<<static_cast<int>(color[2])<<std::endl;

    RGB<uchar> color3 = color * color2;

    std::cout<<static_cast<int>(color3[0])<<"-"<<static_cast<int>(color3[1])<<"-"<<static_cast<int>(color3[2])<<std::endl;




    return 0;
}
