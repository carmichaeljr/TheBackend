## Class: Print
#### Inheritance: None
#### Dependencies: iostream,string
#### Description: A class with a functional interface that contains methods to aid print to a stream, specifically std::cin/std::cout.

### Static Attributes:
1. ```static int indentLevel```
	1. A integer that holds the current indent level. This variable is updated through the ```incrementIndentLevel``` function.

1. ```static int spacesPerIndent```
	1. A integer that defines how many spaces should be considered a "Tab" while outputing to the given stream. This variable is updated through the ```setSpacesPerIndent``` function.

### Static Methods:
1. ```static void init(void)```
	1. Initilizes the print class static attributes to there default variables.

1. ```static void incrementIndentLevel(const int increment)```
	1. Increments the indent level by the specified amount. Negative increment values are acceptable, and are used to "reset" the indenting. The indent level will is always >=0.

1. ```static void setSpacesPerIndent(const int numSpaces)```
	1. Sets the number of spaces that are considered a "Tab". This will be multiplied by the indent level to produce the desired indent level.

1. ```static void print(std::ostream &os, const std::string &str, const bool addEndl=true)```
	1. Prints the given string to the given output stream. If addEndl is true, an endline will be added to the output regardless of the content of ```str```. The current indent level will be output to the given stream before the given string.

1. ```static void printWithoutIndent(std::ostream &os, const std::string &str, const bool addEndl=true)```
	1. Prints the given string to the given output stream. If addEndl is true, an endline will be added to the output regardless of the content of ```str```. The current indent level will **NOT** be output to the given stream before the given string.

1. ```static void error(std::ostream &os, const std::string &errMsg)```
	1. Prints an error message to the given output stream. The given error message will be prepended by this text: ```!Error!" ```. An ```endl``` is added aoutmaticly.

1. ```static void objectDebug(std::ostream &os, const std::string &className, const bool success)```
	1. A function that is specific to debug methods. This will print the success of the object debug operations based on the success flag. The output will either be ```[Ok   ]: ClassName```, or ```[Error]: ClassName```.

1. ```static void objectMethodDebug(std;:ostream &os, const std::string &methodName, const bool success)```
	1. A function that is specific to debug methods. This will print the success of the debug method operations based on the success flag. The output will either be nothing upon success and ```!Error!: MethodName``` if unsuccessfull.

1. ```static bool yesOrNoPrompt(std::ostream &os, std::istream &is, const std::string &question)```
	1. Asks the user the given question and waits for a "y/n" response. True is returned if the response is "y".
