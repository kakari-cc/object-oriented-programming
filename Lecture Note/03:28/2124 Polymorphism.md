## Polymorphism



#### Declared Type vs. Actual Type

---

* Compiler evaluates code based on declared type
* Actual instnace provided at **runtime** can be of a derived type



#### Dynamic Binding

---

**Keyword `virtual`:** method can be refined in subclass and bound to object at **runtime**.

Getting different behaviors from the same code.



#### Overriding a Function Properly

---

**Keyword `override`:** prevent unexpected errors brought by mistake in function name spellings; the base method need to have keyword `virtual` and have the **same signature** (e.g. both `const` or not).



#### Calling a Base Class Method (Outside of Class)

---

````cpp
tigger.Animal::eat();
````

​      1              2           3



> 1. Dervied Class Instance
> 
> 2. Base Class
> 
> 3. Method Call



#### Method Hiding

---

````cpp
// Base...
	void fun(int var)...

// Derived...
  void fun()...
    
// main
  Derived der;
	der.fun(0); // Compilation Error
````

````cpp
// Derived...
	void fun(int var)... // Refined `fun`
    // or...
  using Base::fun
````

