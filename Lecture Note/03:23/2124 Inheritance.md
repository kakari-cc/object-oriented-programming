## Inheritance



#### Code for Inheritance

---

````cpp
class Vehicle {};
class LandVehicle : public Vehicle {};
````

> Need keyword `public`



#### Principle of Substitutability

---

````cpp
class Vehicle {
public:
  void roll() { ... }
}
class Car : public Vehicle{};
class Helicopter : public Vehicle{};
````

> Compiles, but....



#### Inheritance Assignment Rule

---

````cpp
class Base {
  int base_mbr;
};

class Derived : public Base {
  int der_mbr;
}
````

````cpp
Base base;
Derived der;
````

````cpp
base = der;  // ok; slicing, loss of attribute
````

````cpp
der = base;  // compilation error
````



As of pointers;

````cpp
Base* bp;
Derived* dp;
````

````cpp
bp = &der;  // ok
````

````cpp
dp = &base;  // compilation error
````
