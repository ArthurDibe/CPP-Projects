# Aid Management Application (AMA)   
When disaster hits a populated area, the most critical task is to provide immediately affected people with what they need as quickly and as efficiently as possible.<br>
This project creates an application that manages the list of goods that need to be shipped to ae disaster area. The application tracks the quantity of items needed, tracks the quantity on hand, and stores the information in a file for future use. 
<br><br>
There are two categories for the types of goods that need to be shipped:<br>
> \- Non-Perishable goods, such as blankets and tents, which have no expiry date. We refer to goods in this category as Good objects.<br>
> \- Perishable goods, such as food and medicine, that have an expiry date. We refer to goods in this category as Perishable objects.<br>

<br>

## OVERVIEW OF THE CLASSES DEVELOPED
| # | CLASS NAME | DESCRIPTION         |
|---|------------|---------------------|
| 1 | Date       | A class that holds the expiry date of the perishable items.  |
| 2 | Error      | A class that tracks the error state of its client. Errors may occur during data entry and user interaction. |
| 3 | Good       | A class that manages a non-perishable good object |
| 4 | Parishable | A class that manages a perishable good object. This class inherits the structure of the “Good” class and manages a date |
| 5 | iGood      | An interface to the Good hierarchy. This interface exposes the features of the hierarchy available to the application. Any “iGood” class can:<br> \- Read itself from the console or write itself to the console<br> \- Save itself to a text file or load itself from a text file<br> \- Compare itself to a unique C-style string identifier<br> \- Determine if it is greater than another good in the collating sequence<br> \- Report the total cost of the items on hand<br> \- Describe itself<br> \- Update the quantity of the items on hand<br> \- Report its quantity of the items on hand<br> \- Report the quantity of items needed<br> \- Accept a number of items<br> <br> Using this class, the client application can:<br> \- Save its set of iGoods to a file and retrieve that set at a later time<br> \- Read individual item specifications from the keyboard and display them on the screen<br> \- Update information regarding the number of each good on hand<br> |
<br>
## The Client Application - ms5.cpp
The client application manages the iGoods and provides the user with options to:<br>
```    
• List the Goods
• Display details of a Good
• Add a Good
• Add items of a Good
• Update the items of a Good
• Delete a Good
• Sort the set of Goods
```
<br>

___

## Project Class Diagram 
![ms5_image](https://user-images.githubusercontent.com/5942022/129996360-3cd6cc14-1586-4e72-8627-ed82db3a955d.png)
<br><br>

### THE DATE MODULE
The ``Date`` class encapsulates a date that is readable by an ``std::istream`` object and printable by an ``std::ostream`` object using the following format: ``YYYY/MM/DD``, where ``YYYY`` refers to a four-digit value for the year, **MM** refers to a two-digit value for the month and **DD** refers to a two-digit value for the day in the month<br>
<br>
#### THE PRE-DEFINED CONSTANTS:
> •	``min_year`` with the value 2018. This represents the minimum acceptable year for a valid date.<br>
> •	``max_year`` with the value 2038. This represents the maximum acceptable year for a valid date.<br>
> •	``min_date`` with the value 751098. This represents the date 2018/12/30 (see formula below).<br><br>
#### CLASS MEMBERS:
> •	``Year``: a four digit integer between the limits defined above.<br>
> •	``Month``: an integer with the values between 1 and 12 inclusive.<br>
> •	``Day of the Month``: an integer with a value between and the maximum number of days in the month. Use the function int mdays(int year, int month) to find out how many days are in a given month for a given year. Note that February can have 28 or 29 days depending on the year.<br>
> •	``A comparator value`` for comparing the date stored in the current object with the date stored in another Date object. Your constructors set this comparator value and your public relational operators use it to compare dates. (If the value of date one is larger than the value of date two, then date one is more recent than date two; that is, date one is after date two)<br>

> •	``The error state`` which the client of this class can reference to determine if the object holds a valid date, and if not, which part of the date is in error. The possible error states are integer values defined as macros in the ``Date`` class header:

| ERROR NAME      | ERROR NUMBER | ERROR DESCRIPTION |
|------------|--------------|--------------- |
| NO_ERROR   |       0      | -- No error - the date is valid |
| CIN_FAILED |       1      | -- istream failed on information entry - A class that tracks the error state of its client. Errors may occur during data entry and user interaction. |
| DAY_ERROR  |       2      | -- Day value is invalid |
| MON_ERROR  |       3      | -- Month value is invalid |
| YEAR_ERROR |       4      | -- Year value is invalid An interface to the Good hierarchy. This interface exposes the features of the hierarchy available to the application. Any “iGood” class can:<br> \- Read itself from the console or write itself to the console<br> \- Save itself to a text file or load itself from a text file<br> \- Compare itself to a unique C-style string identifier<br> \- Determine if it is greater than another good in the collating sequence<br> \- Report the total cost of the items on hand<br> \- Describe itself<br> \- Update the quantity of the items on hand<br> \- Report its quantity of the items on hand<br> \- Report the quantity of items needed<br> \- Accept a number of items<br> <br> Using this class, the client application can:<br> \- Save its set of iGoods to a file and retrieve that set at a later time<br> \- Read individual item specifications from the keyboard and display them on the screen<br> \- Update information regarding the number of each good on hand<br> |
| PAST_ERROR |       5      | -- Date value is invalid |

<br>

#### **Private Functions to the class**
> •	``void errCode(int errorCode)``: This function sets the error state variable to one of the values listed above.<br>
> •	``int mdays(int year, int month) const``: This function returns the number of days in a given month for a given year.

#### **Constructors**
•	``No argument (default) constructor``:  initializes the object to a safe empty state and sets the error state to NO_ERROR.<br>
•	``Three-argument constructor``: accepts in its parameters integer values for the year, month and day in that order. This constructor checks if each number is in range, in the order of year, month and day and value. If any of the numbers are not within range, this function sets the error state to the appropriate error code and stops further validation. The month value can be between 1 and 12 inclusive). If all of the data received is valid, this constructor stores the values received in the current object, calculates the comparator value, and sets the error state to NO_ERROR.<br>
If any of the data received is not valid, this constructor initializes the object to a safe empty state and sets the comparator value to 0.<br>
The following formula is to set the comparator value for a valid date:<br>
```
year * 372 + month * 31 + day
```
For the date received to be valid its comparator value must be greater than or equal to min_date and all other conditions must be met.<br>
<br>
#### **Relational Operators**
```cpp
bool operator==(const Date& rhs) const;
bool operator!=(const Date& rhs) const;
bool operator<(const Date& rhs) const;
bool operator>(const Date& rhs) const;
bool operator<=(const Date& rhs) const;
bool operator>=(const Date& rhs) const;
```
These comparison operators return the result of comparing the current object as the left-hand side operand with another Date object as the right-hand side operand if the two objects are not empty.<br>
If one or both of the objects is empty, these operators return false.<br>
**For example:** ``operator<`` returns true if the date stored in the current object is before the date stored in ``rhs``; otherwise, this operator returns false. <br>
<br>
#### **QUERIES AND MODIFIERS**
```cpp
•	int errCode() const:
//This query returns the error state as an error code value.

•	bool bad() const: 
//This query returns true if the error state is not NO_ERROR.  

•	std::istream& read(std::istream& istr);
// This function reads the date from the console in the following format: YYYY?MM?DD (e.g. 2016/03/24 or 2016-03-24). 
// This function does not prompt the user. 
// If istr fails at any point (if istr fails, the function istr.fail() returns true), this function sets the error state to CIN_FAILED and does NOT clear istr. 
// If your read() function reads the numbers successfully, and the read values are valid, it stores them into the current object’s instance variables. Otherwise, your function does not change the current object. 
// Regardless of the result of the input process, your function returns a reference to the std::istream object.

•	std::ostream& write(std::ostream& ostr) const;
// This query writes the date to the first parameter in the following format: YYYY/MM/DD, and then returns a reference to the std::ostream object.

```

#### **FREE HELPER FUNCTIONS**
```cpp
•	operator<< // Prints the date to the first parameter (use Date::write()).

•	operator>> // Reads the date from the first parameter (use Date::read()).
```
<br><br>
___
### **THE ERROR MODULE**
The Error class manages the error state of client code and encapsulates the last error message.<br>
Any client can define and store an Error object. If a client encounters an error, the client can set its ``Error`` object to an appropriate message. The client specifies the length of the message.<br>
The Error object reports whether or not any error has occurred.<br>
The ``isClear()`` query on the object reports if an error has occurred. If an error has occurred, the object can display the message associated with that error. The object can be send its message to an std::ostream object.<br>
The class ``Error`` manages a resource and doesn’t support copying operations.<br>
<br>

#### Data Member:
•	A pointer that holds the address of the message, if any, stored in the current object<br>
<br>
#### Public Member Functions:
```cpp
explicit Error(const char* errorMessage = nullptr) 
// This constructor receives the address of a C-style null terminated string that holds an error message. 
// If the address is nullptr, this function puts the object into a safe empty state. 
// If the address points to an empty message, this function puts the object into a safe empty state.
// If the address points to a non-empty message, this function allocates memory for that message and copies the message into the allocated memory. 

destructor
// de-allocates any memory that has been dynamically allocated by the current object.

void clear()
// This function clears any message stored by the current object and initializes the object to a safe empty state.

bool isClear() const
// This query reports returns true if the current object is in a safe empty state.

void message(const char* str)
// This function stores a copy of the C-style string pointed to by str.
// De-allocates any memory allocated for a previously stored message.
// If str points to a non-empty message, this function allocates the dynamic memory needed to store a copy of str (remember to include 1 extra byte for the null terminator) and copies the message into that memory.
// If str points to an empty message, this function puts the current object in a safe empty state.

const char* message() const
// If the current object is not in a safe empty state, this query returns the address of the message stored in the object.
// If the current object is in a safe empty state, this query returns nullptr. 
```
<br>

#### **Free Helper Functions**
```cpp
operator<<
// This operator sends an Error message, if one exists, to an std::ostream object and returns a reference to the std::ostream object. 
// If no message exists, this operator does not send anything to the std::ostream object and returns a reference to the std::ostream object
```
<br>

___
## THE GOOD MODULE
The ``Good`` class is a concrete class that encapsulates the general information for an aid ``Good``<br>
Define and implement your ``Good`` class in the ``aid`` namespace.<br>
Your ``Good`` class uses an ``Error`` object, but does not need a ``Date`` object<br>
<br>
### PRE-DEFINED CONSTANTS
•	``max_sku_length``: Maximum number of characters in a SKU (stock keeping unit) – 7<br>
•	``max_unit_length``: Maximum number of characters in the units’ descriptor for a Good – 10<br>
•	``max_name_length``: Maximum number of characters in the user’s name descriptor for a Good length – 75<br>
•	``tax_rate``: The current tax rate – 13%<br>
<br>
#### PROTECTED MEMBER FUNCTIONS
```cpp
void name(const char*)
// This function receives the address of a C-style null-terminated string that holds the name of the Good. This function
// Stores the name of the Good in dynamically allocated memory;
// Replaces any name previously stored;
// If the incoming parameter is the nullptr address, this function removes the name of the Good, if any, from memory.

const char* name() const
// This query returns the address of the C-style null-terminated string that holds the name of the Good. If the Good has no name, this query returns nullptr.

const char* sku() const
// This query returns the address of the C-style null-terminated string that holds the SKU of the Good. 

const char* unit() const
// This query returns the address of the C-style null-terminated string that holds the unit of the Good.

bool taxed() const
// This query returns the taxable status of the Good.

double itemPrice() const
// This query returns the price of a single item of the Good without tax.

double itemCost() const
// This query returns the price of a single item of the Good plus any tax that applies to the Good.

void message(const char*)
// This function receives the address of a C-style null-terminated string holding an error message and stores that message in the Error object to the current object.

bool isClear() const
// This query returns true if the Error object is clear; false otherwise.
```
<br>

#### HELPER FUNCTIONS
```cpp
bool operator>(const iGood&) const

std::ostream& operator<<(std::ostream&, const Good&)
// This helper receives a reference to an std::ostream object and an unmodifiable reference to a Good object and returns a reference to the std::ostream object. Your implementation of this function will insert a Good record into the std::ostream

std::istream& operator>>(std::istream&, Good&)
// This helper receives a reference to an std::istream object and a reference to a Good object and returns a reference to the std::istream object. Your implementation of this function extracts the Good record from the std::istream.

double operator+=(double&, const Good&)
// This helper receives a reference to a double and an unmodifiable reference to a Good object and returns a double. Your implementation of this function adds the total cost of the Good object to the double received and returns the updated double
```
<br>

___
### THE iGOOD INTERFACE
The ``iGood`` class is an interface that exposes the Good hierarchy to client applications. This class is abstract and cannot be instantiated.<br>
<br>
The definition of your iGood interface includes the following pure virtual member functions:
```cpp
std::fstream& store(std::fstream& file, bool newLine = true) const
// This query will receive a reference to an std::fstream object and an optional bool and return a reference to the std::fstream object. The bool argument will specify whether or not a newline should be inserted after each iGood record. Implementations of this function will insert the Good records into the std::fstream object

std::fstream& load(std::fstream& file)
// This modifier will receive a reference to an std::fstream object and return a reference to that std::fstream object. Implementations of this function will extract iGood records from the std::fstream object.
std::ostream& write(std::ostream& os, bool linear) const
// This query will receive a reference to an std::ostream object and a bool and return a reference to the std::ostream object. The bool argument will specify whether or not the records should be listed on a single line or on separate lines. Implementations of this function will insert the iGood record for the current object into the std::ostream object.

std::istream& read(std::istream& is)
// This modifier will receive a reference to an std::istream object and returns a reference to the std::istream object. Implementations of this function will extract the iGood record for the current object from the std::istream object.

bool operator==(const char*) const
// This query will receive the address of an unmodifiable C-style null-terminated string and return true if the string is identical to the stock keeping unit of an iGood record; false otherwise

double total_cost() const
// This query will return the cost of a single unit of an iGood with taxes included.
const char* name() const

// This query will return the address of a C-style null-terminated string containing the name of an iGood.

void quantity(int)
// This modifier will receive an integer holding the number of units of an iGood that are currently available. This function will set the number of units available

int qtyNeeded() const
// This query will return the number of units of an iGood that are needed

int quantity() const
// This query will return the number of units of an iGood that are currently available

int operator+=(int)
// This modifier will receive an integer identifying the number of units to be added to the iGood and return the updated number of units currently available

bool operator>(const iGood&) const
// This query will receive an unmodifiable reference to an iGood object and return true if the current object is greater than the referenced iGood object; false otherwise
``` 
<br>

The following helper functions support the interface:
```cpp
std::ostream& operator<<(std::ostream&, const iGood&)
// This helper function will receive a reference to an std::ostream object and an unmodifiable reference to an iGood object and return a reference to the std::ostream object. Implementations of this function will insert the iGood record for the referenced object into the ostream object

std::istream& operator>>(std::istream&, iGood&)
// This helper function will receive a reference to an std::istream object and a reference to an iGood object and return a reference to the std::istream object. Implementations of this function will extract the iGood record for the referenced object from the std::istream object

double operator+=(double&, const iGood&)
// This helper function will receive a reference to a double and an unmodifiable reference to an iGood object and return a double. Implementations of this function will add the total cost of the iGood object to the double received and return the updated value of the double

iGood* CreateProduct(char tag)
// This helper function will return the address of a iGood object or nullptr
```
<br>

___
### THE PERISHABLE CLASS
The Perishable class is a separate concrete class that encapsulates information for perishable goods.<br>
<br>

#### PRIVATE DATA
•	A ``Date`` object holds the expiry date for the perishable good.<br>
<br>

#### PUBLIC MEMBER FUNCTIONS
```cpp
Default Constructor
// This constructor passes the file record tag for a perishable good (‘P’) to the base class constructor and sets the current object to a safe empty state

std::fstream& store(std::fstream& file, bool newLine = true) const
// This query receives a reference to an fstream object and an optional bool and returns a reference to the modified fstream object. This function stores a single file record for the current object. This function
//  - Calls its base class version passing as arguments a reference to the fstream object and a false flag. The base class inserts the common data into the fstream object
//  - Inserts a comma into the file record 
//  - appends the expiry date to the file record. 
//  - If newLine is true, this function inserts a newline character (‘\n’) before exiting. In this case, the file record created will look something like:
//
//      P,1234,water,1.5,0,1,liter,5,2018/03/28<ENDL> 
//
// - If newLine is false, this function does not insert a newline character (‘\n’) before exiting. In this case, the file record created will look something like:
//
//      P,1234,water,1.5,0,1,liter,5,2018/03/28
//
// Note that the first field in the file record is ‘P’. This character was passed to the base class at construction time and is inserted by the base class version of this function.

std::fstream& load(std::fstream& file)
// This modifier receives a reference to an fstream object and returns a reference to that fstream object. This function extracts the data fields for a single file record from the fstream object. This function: 
//  - Calls its base class version passing as an argument a reference to the fstream object
//  - Loads the expiry date from the file record using the read() function of the Date object
//  - Extracts a single character from the fstream object.

std::ostream& write(std::ostream& os, bool linear) const
// This query receives a reference to an ostream object and a bool flag and returns a reference to the modified ostream object. The flag identifies the output format. This function:
//  - Calls its base class version passing as arguments a reference to the ostream object and the bool flag. 
//  - If the current object is in an error or safe empty state, does nothing further. 
//  - If the current object is not in an error or safe empty state, inserts the expiry date into the ostream object. 
//  - If linear is true, adds the expiry date on the same line for an outcome that looks something like this:
//
//      1234   |water               |   1.50|   1|liter     |   5|2018/12/30
//
//  - If linear is false, this function adds a new line character followed by the string “Expiry date: ” and the expiry date for an outcome something like this:
//
//      Sku: 1234
//      Name (no spaces): water
//      Price: 1.50
//      Price after tax: N/A
//      Quantity on hand: 1 liter
//      Quantity needed: 5
//      Expiry date: 2018/12/30
//
// This function does not insert a newline after the expiry date in the case of linear output (linear is true) or the case of line-by-line output (linear is false).

std::istream& read(std::istream& is)
// This modifier receives a reference to an istream object and returns a reference to the modified istream object. This function populates the current object with the data extracted from the istream object
// This function calls its base class version passing as its argument a reference to the istream object. If the base class object extracts data successfully, this function prompts for the expiry date and stores it in a temporary Date object. The prompt looks like with a single space after the colon:
//
//      Expiry date (YYYY/MM/DD):
//
// If the temporary Date object is in an error state, this function stores the appropriate error message in the base class’ error object and sets the state of the istream object to a failed state. The member function that sets it to a failed state is (istream::setstate(std::ios::failbit)). The messages that correspond to the error codes of a Date object are:
//
//      CIN_FAILED:		Invalid Date Entry
//      YEAR_ERROR:	    Invalid Year in Date Entry
//      MON_ERROR:  	Invalid Month in Date Entry
//      DAY_ERROR:		Invalid Day in Date Entry
//      PAST_ERROR: 	Invalid Expiry Date in Date Entry
//
// If the istream object is not in an error state, this function copy assigns the temporary Date object to the instance Date object. The member function that reports failure of an istream object is istream::fail().


const Date& expiry() const
// This query returns the expiry date for the perishable product.
```
<br>

#### FREE HELPER FUNCTIONS
```cpp
iGood* CreateProduct(char tag)
// This helper function will dynamically create and return the address of an iGood object:
//      - if the parameter is ‘N’ or ‘n’, this function creates a Good object
//      - if the parameter is ‘P’ or ‘p’, this function creates a Perishable object
//      - returns nullptr otherwise
```