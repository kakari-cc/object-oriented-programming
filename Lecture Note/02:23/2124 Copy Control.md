## Copy Control - *Feburary 23*



#### Responsibilities of Assignment Operator

* Get rid of previous value

* Replace previous value

* Copy values from object on "right-hand side" of operator

* Return value of proper type*

* Check for self-assignment

> Implemented as a member method



*Why is **4** necessrary:

````cpp
int x, y, z = 10;
x = y = z;
````

Expression `(y = z)` needs to be able to return `10` to support this C++ feature.



````cpp
SimpleClass& operator=(const SimpleClass& rhs) {
  if(this != &rhs) {
    // free up resources (as needed)
    delete ptr;
    // allocate new resources (as needed)
    ptr = new int;
    //copy over all data
    *ptr = *rhs.ptr
  }
  return *this;
}
````

---



#### Vector Implementation

* every vector uses 24 bytes (minimum)
* data stored in array on the heap



````cpp
class Vector {
public:
private:
  int* data;
  size_t the_size, the_capacity;
}
````

