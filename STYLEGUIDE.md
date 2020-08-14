# Style Guide
*This document is a work in progress!*
Please follow the rules outline in the document below when contributing.

### Classes
1. In a classes initializer list, super class initializers go before any member variables.
1. In a class, the order of attributes should go ```public```,```protected```, then ```private```.
1. Unless explicitly only needed for the private implementation of a class, all attributes should be declared ```protected```.
1. All comparison operators will be declared as friend functions above any public/protected/private class definitions.
1. Place ```static``` class attributes in there own public/protected/private namespace header above the non static members. This makes it easier to differentate what is a class attribute and what is an object attribute.
	1. *A good example of the above rule is the ```XMLTag``` class defined in the ```XMLTag.hpp``` header file.*
1. Place "pass through" interfaces under there own separate public/protected/private namespace header below the classes other methods. A "pass through" interface is used when inheritance is not an option, like the ```STL``` containers where virtual destructors are used.
	1. *A good example of the above rule is the ```XMLTag``` class defined in the ```XMLTag.hpp``` header file.*
1. In the implementation file for a class, the public methods come first in order that they appear in the definition of the class.
1. The order of methods in a classes implementation should follow the order below. With the exception of the first section, division lines should be insterted between the sections.
	1. *A good example of the above rule is on the ```File``` class implemented in the ```File.cpp``` file.*
	1. Public
	1. Protected
	1. Private
	1. Friend
	1. Class
	1. Inner classes (Place in separate file if large enough to warrant)
