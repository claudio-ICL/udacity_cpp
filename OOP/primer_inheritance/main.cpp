#include "things.h"
int main() {
  Circle c = Circle(12.5);
  c.info();
  c.set("diameter", 10.0);
  c.info();
  Wheel w = Wheel(10.0, "rubber");
  w.info();
  w.geometry();
  w.set("radius", 1.0);
  w.Material("iron");
  w.info();
  w.geometry();
  w.howmany();
  Bike b;
  b.color = "green";
  b.kickstand = true;
  b.set_wheels(2, 2, "aluminium");
  b.info();
  w.howmany();
  Car car;
  car.color = "red";
  car.set_wheels(4, 0.2, "rubber");
  car.info();
  w.howmany();
  return 0;
}
