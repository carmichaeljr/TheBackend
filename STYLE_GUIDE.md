# Style Guide
Please follow the rules outline in the document below when contributing.

###Classes
1. Place ```static``` class members in there own public/protected/private namespace header above the non static members. This makes it easier to differentate what is a class member and what is an object member.
1. Place "pass through" interfaces (ie. Mimicking all vector methods to access a private vector within a class) under there own separate public/protected/private namespace header below the classes other methods.
	1. A good example of the above mentioned rules are in the ```XMLTag.hpp``` header file.
