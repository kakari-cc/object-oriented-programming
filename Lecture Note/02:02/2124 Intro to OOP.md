## Intro to OOP - *Febuary 02-07*



#### Initialization List Syntax

````cpp
class Vorlon {
  public:
  	Vorlon(int param) : var(7) {}
  	// Constructor
  	int var;
};
````



> Mark methods that do not modify the current object as `const`.



#### Operator Overload

---

**Wanted Behavior:**

````cpp
Cat cat("Kitty");
cout << cat << endl;
````



**Overloading the Output Operator `<<`**

````cpp
ostream& operator<< (ostream& os, const Cat& thd) {
  os << "^&*&^&*$%";
  return os;
}
````



**`friend` Modifier**

````cpp
class Cat {
  // Function Prototype
  friend ostream& operator<<(ostream&, const Cat&)
    ...
};

// Output Operator Overload Function
````



#### Nested Types

---

````cpp
class Date {
  ...
};

class Vorlon {
public:
  Vorlon(const string& a_name, int b_month) : my_name(), b_day(b_month) {}
  // Date is only accessible through Vorlon
  // Use `Vorlon::Date`
  
private:
  const string my_name
    Date b_day;
}
````

