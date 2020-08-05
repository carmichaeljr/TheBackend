## Class: Tokenizer
#### Inheritance: None
#### Dependencies: vector,string
#### Description: A class that parses a string and splits it into segments given certain tokens. This class has a "pass-through" vector interface.

The rules for parsing the given string are defined by "inclusion" token pairs, "exclusion" token pairs, and "split" tokens.
	* Inclusion token pairs: these are token pairs that include everything in between them, including other tokens, except other inclusion tokens. This is done so that inclusion tokens can be nested, making the below example possible.
		* Inclusion Pairs: 	<> ""
		* Parse String:		<Name attr=">">
		* Correct parsing:	Name attr=">"
		* Incorrect parsing: 	Name attr="
	* Exclusion token pairs: these are token pairs that exclude everything between them, including other tokens.
	* Split tokens: these are tokens that do not need to match with another token, and when encountered just create another segment from the previous found token to the current one.
The error state of the object is set during the parse call, and can be retrived from the rdstate method. Error states are bitwise or'ed together, allowing for the detection of multiple errors in a single variable.

### Static Attributes:
1. ```static const int parseSuccess=0```
	1. A flag that is used to compare an objects error code against after parsing a string. If the objects error code is equal to ```parseSuccess```, then no parsing errors were encountered.

1. ```static const int unballancedTokens=1```
	1. A flag that is used to compare an objects error code against after parsing a string. If the objects error code is equal to ```unballancedTokens``` then it means that an exclusion and/or inclusion token pair did not have both the opening token and the coresponding closing token.

### Public Methods:
1. Constructor:
	1. ```Tokenizer(void)```
		1. Creates a blank Tokenizer object.
	1. ```Tokenizer(const Tokenizer &other)```
		1. The copy constructor.
	1. ```Tokenizer(const Tokenizer &&other)```
		1. The move constructor. Note that this class does not use any special resources, which means that this essentially funcitons as another copy constructor.

1. ```Tokenizer& operator=(const Tokenizer &other)```
	1. The copy assignment operator.

1. ```Tokenizer& operator=(const Tokenizer &&other)```
	1. The move assignment operator.

1. ```void addSplitTokens(const std::string &tokens)```
	1. Given a list of new split tokens in the form of a string, new tokens will be added to the objects internal list if they are not already present.

1. ```const std::string getSplitTokens(void)```
	1. Returns a const reference to the objects internal list of split tokens.

1. ```void addInclusionTokens(const std::string)```
	1. Given a list of token pairs in the form of a string, new inclusion token pairs will be added to the objects internal list if they are not already present.

1. ```const std::vector<std::string> getInclusionTokens(void)```
	1. Returns a const reference to the objects internal list of inclusion tokens.

1. ```void addExclusionTokens(const std::string)```
	1. Given a list of token pairs in the form of a string, new exclusion token pairs will be added to the objects internal list if they are not already present.

1. ```const std::vector<std::string> getExclusionTokens(void)```
	1. Returns a const reference to the objects internal list of exclusion tokens.

1. ```void parse(const std::string &raw, const bool keepTokens=false)```
	1. Parses a string into segments using the objects current split, inclusion, and exclusion tokens. These tokens are set through there respective get and set methods outlined above. If an error is encountered, the objects error flag will be set accordingly. This error code can then be retreved from a ```rdstate``` call. Error states are bit-wise or'ed together, allowing for the detection of multiple errors in a single flag. If the ``keepTokens``` flag is set to true, then tokens will be added as there own separate segments in the final parsed string.

1. ```bool good(void) const```
	1. Returns weather or not any errors were thrown durring the previous parse call. Returns true if no errors were encountered.

1. ```int rdstate(void) const```
	1. Returns the error state set in the previous parse call. These error codes can then be compared to the classes error codes.

1. Vector "pass-through" interface methods. Unless otherwise noted they all behave the same as the equivilent vector methods.
	1. ```std::string& at(const int index)```
	1. ```const std::string& at(const int index) const```
	1. ```std::string& operator[](const int index)```
	1. ```const std::string& operator[](const int index) const```
	1. ```std::string& front(void)```
	1. ```const std::string& front(void) const```
	1. ```std::string& back(void)```
	1. ```const std::string& back(void) const```
	1. ```std::vector<std::string>::iterator begin(void)```
	1. ```const std::vector<std::string>::const_iterator begin(void) const```
	1. ```std::vector<std::string>::iterator end(void)```
	1. ```const std::vector<std::string>::const_iterator end(void) const```
	1. ```std::vector<std::string>::const_iterator cbegin(void)```
	1. ```std::vector<std::string>::const_iterator cend(void)```
	1. ```bool empty(void) const```
	1. ```unsigned int size(void) const```
	1. ```void clear(void)```

### Protected Attributes:
1. ```int error=Tokenizer::parseSuccess```
	1. The internal error code of the object is set in this variable while parsing a string. The default value is "parseSuccess".

1. ```std::vector<std::string> segments```
	1. The internal vector that holds the segments after parsing a string. This vector is accessed through the "pass-through" vector interface.

1. ```std::vector<std::string> inclusionTokens```
	1. The internal data structure that holds inclusion tokens. These are set through the public ```addExclusionTokens``` method.

1. ```std::vector<std::string> exclustionTokens```
	1. The internal data structure that holds exclusion tokens. These are set through the public ```addInclusionTokens``` method.

1. ```std::string splitTokens```
	1. The internal data structure that holds split tokens. These are set through the public ```addSplitTOkens``` method.
