#include <iostream>
#include "Image.h"
#include "RGB.h"

#include<vector>

int main()
{

    Image< RGB<uchar> > image;
    image.Read("/home/oscar/OpenCV_Example/image.jpg");

    return 0;
}
