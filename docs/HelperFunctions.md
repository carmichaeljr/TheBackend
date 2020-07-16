## Class: HelperFunc
#### Inheritance: None
#### Dependencies: string
#### Description: A class with a functional interface that contains methods to aid common operations, such as string manipulation.

### Static Attributes:
1. ```static const std::string whitespace```
	1. A string that contains characters that represent white space.

### Static Methods:
1. ```static void removeTrailingNull(std::string &str)```
	1. Removes the trailing null from a string. Usefull for converting "c" style strings to ```std::string```.

1. ```static void trimWhitespaceAtEnd(std::string &str)```
	1. Removes characters at the end of a string that are contained in the ```whitespace``` class variable. If a trailing Null character is found, it is removed also.

1. ```static void trimWhitespaceAtStart(std::string &str)```
	1. Removes characters at the beginning of a string that are contained in the ```whitespace``` class variable.

1. ```static void trimWhitespace(std::string &str)```
	1. Removes characters at the beginning and end of a string that are contained in the ```whitespace``` class variable. This is effectively the same as consecutive calls to ```trimWhitespaceAtEnd``` and ```trimWhitespaceAtStart```.
