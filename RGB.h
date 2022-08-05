#ifndef RGB_H
#define RGB_H

#include <vector>
#include <iostream>
#include <cmath>

template<typename Type=unsigned char> //deep
class RGB //Pixel//Color
{
public:
    RGB();

    const Type& operator[](unsigned index) const {return Channels[index];}
    Type& operator[](unsigned index) {return Channels[index];}

    using ValueType = Type;

    //Sobrecarga de operadores
    RGB<Type> operator+ (const Type& a)
    {
        float depth = sizeof(Type)*8;
        float values = std::pow(2, depth);
        //std::cout<<values<<std::endl;

        RGB<Type> result;

        //Restriccion cuando se pasa de los valores permitidos
        for(unsigned i = 0; i < result.Channels.size(); ++i)
        {
            float temp = Channels[i] + a;
            result.Channels[i] = (temp < values) ? temp : values-1;
                //std::cout<<"Hola"<<std::endl;
        }
        return result;
    }

    RGB<Type> operator- (const Type& a)
    {

        RGB<Type> result;

        //Restriccion cuando se pasa de los valores permitidos
        for(unsigned i = 0; i < result.Channels.size(); ++i)
        {
            float temp = Channels[i] - a;
            result.Channels[i] = (temp > 0) ? temp : 0;
        }
        return result;
    }

    RGB<Type> operator* (const Type& a)
    {
        float depth = sizeof(Type)*8;
        float values = std::pow(2, depth);
        //std::cout<<values<<std::endl;

        RGB<Type> result;

        //Restriccion cuando se pasa de los valores permitidos
        for(unsigned i = 0; i < result.Channels.size(); ++i)
        {
            float temp = Channels[i] * a;
            result.Channels[i] = (temp < values) ? temp : values-1;
                //std::cout<<"Hola"<<std::endl;
        }
        return result;
    }

    RGB<Type> operator/ (const Type& a)
    {
        RGB<Type> result;
        for(unsigned i = 0; i < result.Channels.size(); ++i)
        {
            float temp = (a == 0) ? Channels[i] : Channels[i]/a;
            result.Channels[i] = temp;
        }
        return result;
    }

    //Sobrecarga de operadores pixel wise
    RGB<Type> operator+ (const RGB<Type>& other)
    {
        float depth = sizeof(Type)*8;
        float values = std::pow(2, depth);
        //std::cout<<values<<std::endl;

        RGB<Type> result;

        //Restriccion cuando se pasa de los valores permitidos
        for(unsigned i = 0; i < result.Channels.size(); ++i)
        {
            float temp = Channels[i] + other.Channels[i];
            result.Channels[i] = (temp < values) ? temp : values-1;
                //std::cout<<"Hola"<<std::endl;
        }
        return result;
    }

    RGB<Type> operator- (const RGB<Type>& other)
    {

        RGB<Type> result;

        //Restriccion cuando se pasa de los valores permitidos
        for(unsigned i = 0; i < result.Channels.size(); ++i)
        {
            float temp = Channels[i] - other.Channels[i];
            result.Channels[i] = (temp > 0) ? temp : 0;
        }
        return result;
    }

    RGB<Type> operator* (const RGB<Type>& other)
    {
        float depth = sizeof(Type)*8;
        float values = std::pow(2, depth);
        //std::cout<<values<<std::endl;

        RGB<Type> result;

        //Restriccion cuando se pasa de los valores permitidos
        for(unsigned i = 0; i < result.Channels.size(); ++i)
        {
            float temp = Channels[i] * other.Channels[i];
            result.Channels[i] = (temp < values) ? temp : values-1;
                //std::cout<<"Hola"<<std::endl;
        }
        return result;
    }

private:

    std::vector<Type> Channels{}; //vector size 3

};

template<typename Type>
RGB<Type>::RGB(): Channels{std::vector<Type>(3, {})}
{

}

#endif // RGB_H
