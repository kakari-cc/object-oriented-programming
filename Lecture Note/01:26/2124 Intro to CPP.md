## Intro to C++ - *January 26-31*



#### New Syntax from C++ 11 Standard

> Ranged `for`

````cpp
vector<int> vec;
for (int value : vec) {
  ...
}
````



#### C++ Way of File Processing

>  `fstream`

````cpp
ifstream jab("jabberwocky");
if (!jab) {
  cerr << "failed to open";
  exit(1);
}
string s;
````
+
````cpp
getline(jab, s);
````
or
````cpp
jab >> s;
````
+
````cpp
cout << s << endl;
jab.close();
````



#### Three ways to pass arguments to functions:

1. Pass by Value
2. Pass by Reference
3. Pass by Pointer
