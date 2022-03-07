## Cyclic Association



#### Cyclic Dependencies

---

````cpp
class A {
  B x;  // Compile Error: Class B must be defined first
};
````

````cpp
class D;  // Forward declaration

class C {
  D* y;  // Only requires D to be a valid type
};
````

...

````cpp
class D {
  C* z;
};

class C {
  D* y;  // Problematic...
};
````

**Forward declarations** necessary.

* no size info
* no details on member vars and funcs
* **only** provides name of the type



When forward declaration cannot solve the problem...

````cpp
class C;

class D {
public:
  void d_func();
private:
  C* z;
};

class C {
public:
  void c_func() {}
private:
  D* y;
}

void D::d_func() { z->c_func(); }
````



````cpp
void D::d_func() { z->c_func(); }
````

​                ↑

`scope resolution operator`