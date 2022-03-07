## Pointer - *Feburary 09-14*



#### Syntax

---

````cpp
int* a;
int * a;
int *a;
````

All OK

````cpp
int* a, b;
````

`a` is a pointer to `int`, but `b` is a regular `int`.



#### Place Holder for Pointer Initilization

---

`pullptr`



#### Arrow Operator

---

````cpp
(*object).member;
````



`.` has higher priority than `*`, so `()` is needed when accessing object members;

````cpp
pre->method();
````

`->` enable member access.



#### Const Pointer

---

````cpp
int x = 1, y;
int* const ptr = &x;
*ptr = 2; // OK, Underlying Value Can Be Changed
ptr = &y; // COMPILE ERR
````

````cpp
int x = 1, y;
const int* ptr = &x;
ptr = &y; // OK, Address Pointed to Can Be Changed
*ptr = 2; // COMPILE ERR
````

````cpp
int x = 1, y;
const int* const ptr = &x;
*ptr = 2; // COMPILE ERR
ptr = &y; // COMPILE ERR
````

