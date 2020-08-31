#include "things.h"
Circle::Circle(float d) : diameter(d) {
  compute("radius");
  compute("area");
}
void Circle::compute(std::string what) {
  if (what == "radius") {
    radius = diameter / 2;
  } else if (what == "diameter") {
    diameter = radius * 2;
  } else {
    area = pi * radius * radius;
  }
}
float Circle::get(std::string what) {
  if (what == "radius") {
    return radius;
  } else if (what == "diameter") {
    return diameter;
  } else {
    area = pi * radius * radius;
  }
}
void Circle::set(std::string what, float value) {
  if (what == "radius") {
    radius = value;
    compute("diameter");
  } else if (what == "diameter") {
    diameter = value;
    compute("radius");
  }
  compute("area");
}
void Circle::info() {
  std::cout << "radius: " << radius << std::endl;
  std::cout << "diameter: " << diameter << std::endl;
  std::cout << "area: " << area << std::endl;
}
int Wheel::tot{0};
Wheel::Wheel(float d, std::string m) : Circle(d), material(m) {
  compute("radius");
  compute("area");
  NewId();
}
void Wheel::NewId() { id = ++tot; }
void Wheel::info() {
  std::cout << "Wheel numer: " << id << "/" << tot << std::endl;
  std::cout << "Wheel diameter: " << get("diameter") << std::endl;
  std::cout << "Wheel material: " << material << std::endl;
}
void Wheel::geometry() { Circle::info(); }
void Wheel::howmany() {
  std::cout << "Tot wheels: " << Wheel::tot << std::endl;
  std::cout << "\n";
}
void Vehicle::set_wheels(int n, float d, std::string m) {
  num_wheels = n;
  wheels.clear();
  wheelsids = new int[n];
  for (int i = 0; i < n; i++) {
    wheels.push_back(Wheel(d, m));
    *(wheelsids + i) = Wheel::tot;
  }
}
void Vehicle::info(bool geom) {
  std::cout << name << " color: " << color << std::endl;
  std::cout << name << " wheels identifiers: ";
  for (int i = 0; i < num_wheels; i++) {
    std::cout << *(wheelsids + i) << ", ";
  }
  std::cout << "\n";
  for (int i = 0; i < num_wheels; i++) {
    wheels[i].info();
    if (geom) {
      wheels[i].geometry();
    }
  }
  std::cout << "\n";
}
void Car::info(bool geom) {
  std::cout << "Car type: " << type << std::endl;
  Vehicle::info(geom);
}
void Bike::info(bool geom) {
  std::cout << "Bike kickstand: " << kickstand << std::endl;
  Vehicle::info(geom);
}
