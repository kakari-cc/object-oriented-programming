## Separate Compilation



#### Separate Compilation

---

**Split files to increase uability.**

* Class Definition `*.h`
  * Method Prototype
  * Associated Function Prototype
* Class Implementation `.cpp`
  * Method Definition
  * Associated Function Definition
* `main` Program `.cpp`
  * `main` Function Definition

> Fully quzlified name ``std::` in header files to avoid name collision.



#### Namespace

---

**Making names unambiguous.**

> A `namespce` allows names to be shared within a program.

````cpp
namespace CS2124 {
  ...
}
````



#### Include Guards

---

````cpp
#ifndef <identifier_name>
#define <identifier_name>
#endif
````

