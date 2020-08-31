#ifndef THINGS_H
#define THINGS_H
#include<iostream>
#include<vector>
#include<string>
class Circle{
  private:
    static constexpr float pi{3.14159};
    float diameter;
    float radius;
    float area;
  public:
    Circle(float);
    float get(std::string);
    void set(std::string, float);
    void compute(std::string);
    void info();
};
class Wheel: public Circle{
  public:
    static int tot;
    Wheel(float, std::string );
    void Material(std::string m){material=m;}
    void info();
    void geometry();
    void howmany();
  private:
    int id;
    std::string material{"rubber"};
    void NewId();
};
class Vehicle{
  private:
    std::vector<Wheel> wheels;
    int num_wheels;
    int* wheelsids;
  public:
    std::string name{"Vehicle"};
    std::string color;
    void set_wheels(int, float, std::string);
    void info(bool=false);
};
class Car: public Vehicle{
  public:
    Car() {name="Car";}
    std::string type{"sedan"};
    void info(bool=false);
};
class Bike: public Vehicle{
  public:
    Bike() {name="Bike";}
    bool kickstand{false};
    void info(bool=false);
};
#endif


