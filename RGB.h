#ifndef RGB_H
#define RGB_H

#include <vector>

template<typename Type=unsigned char> //deep
class RGB //Pixel//Color
{
public:
    RGB();

    const Type& operator[](unsigned index) const {return Channels[index];}
    Type& operator[](unsigned index) {return Channels[index];}


    using ValueType = Type;

private:

    std::vector<Type> Channels{}; //vector size 3

};

template<typename Type>
RGB<Type>::RGB(): Channels{std::vector<Type>(3, {})}
{

}

#endif // RGB_H
