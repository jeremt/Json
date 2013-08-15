Json
====

Very easy to use and intinctive implementation of Json c++ object.

Usage
-----

Simply include the _Json.hpp_ file into your project and use it, example:

```
#include <iostream>
#include "Json.hpp"

int main() {
  Json myConfig;
  
  myConfig.load("myConfig.json");
  std::cout << "Project name is " << myConfig["name"] << std::endl;
  return 0;
}
```
