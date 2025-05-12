// James Magana
// Lab 8
#include <iostream>
#include <string>
#include <limits>
#include <sstream>

using namespace std;

class FractionException {
private:
    string errorMessage;
public:
    FractionException(const string& message);
    const string& getErrorMessage() const;
};

class Fraction {
private:
    int numerator = 1;
    int denominator = 1;
    static int objectCount;
    static const int DEFAULT_NUMERATOR = 1;
    static const int DEFAULT_DENOMINATOR = 1;

    void validateFraction(int wholeNumber, int numeratorValue, int denominatorValue) const;

public:
    Fraction();
    Fraction(int wholeNumber);
    Fraction(int numeratorValue, int denominatorValue);
    Fraction(int wholeNumber, int numeratorValue, int denominatorValue);
    Fraction(const Fraction& other);
    ~Fraction();

    void setNumerator(int numeratorValue);
    void setDenominator(int denominatorValue);
    void setFraction(int wholeNumber);
    void setFraction(int numeratorValue, int denominatorValue);
    void setFraction(int wholeNumber, int numeratorValue, int denominatorValue);

    string toString() const;
    static int getObjectCount();
    int getNumerator() const;
    int getDenominator() const;
    
    bool operator==(const Fraction& other) const;
    Fraction& operator=(const Fraction& other);
    friend istream& operator>>(istream& is, Fraction& fraction);
    friend ostream& operator<<(ostream& os, const Fraction& fraction);
};

enum MenuOption { 
    DEMO_OPERATORS = 1, 
    QUIT 
};

void testEqualityOperator();
void testAssignmentOperator();
void testOutputOperator();
void testInputOperator();
void demonstrateOperators();
void printMenu();

int main() {
    int choice;
    do {
        printMenu();
        cin >> choice;

        switch (choice) {
            case DEMO_OPERATORS:
                demonstrateOperators();
                break;
            
            case QUIT:
                break;
            
            default:
                cout << "Invalid input. Please try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (choice != QUIT);

    return 0;
}

// Static member initialization
int Fraction::objectCount = 0;

// FractionException member definitions
FractionException::FractionException(const string& message) : errorMessage(message) {}

const string& FractionException::getErrorMessage() const { 
    return errorMessage; 
}

// Fraction member definitions
void Fraction::validateFraction(int wholeNumber, int numeratorValue, int denominatorValue) const {
    bool isValid = true;
    string validationError;
    
    if (denominatorValue == 0) {
        isValid = false;
        validationError = "Denominator cannot be zero.";
    }
    else if (wholeNumber < 0 || numeratorValue < 0 || denominatorValue < 0) {
        isValid = false;
        validationError = "Fraction components cannot be negative.";
    }
    if (!isValid) {
        throw FractionException(validationError);
    }
}

Fraction::Fraction() : numerator(DEFAULT_NUMERATOR), denominator(DEFAULT_DENOMINATOR) {
    objectCount++;
}

Fraction::Fraction(int wholeNumber) : numerator(wholeNumber), denominator(1) {
    validateFraction(0, numerator, denominator);
    objectCount++;
}

Fraction::Fraction(int numeratorValue, int denominatorValue) : numerator(numeratorValue), denominator(denominatorValue) {
    validateFraction(0, numerator, denominator);
    objectCount++;
}

Fraction::Fraction(int wholeNumber, int numeratorValue, int denominatorValue) {
    validateFraction(wholeNumber, numeratorValue, denominatorValue);
    numerator = wholeNumber * denominatorValue + numeratorValue;
    denominator = denominatorValue;
    objectCount++;
}

Fraction::Fraction(const Fraction& other) : numerator(other.numerator), denominator(other.denominator) {
    objectCount++;
}

Fraction::~Fraction() {
    numerator = 0;
    denominator = 1;
    objectCount--;
}

void Fraction::setNumerator(int numeratorValue) {
    setFraction(0, numeratorValue, denominator);
}

void Fraction::setDenominator(int denominatorValue) {
    setFraction(0, numerator, denominatorValue);
}

void Fraction::setFraction(int wholeNumber) {
    setFraction(wholeNumber, DEFAULT_NUMERATOR, DEFAULT_DENOMINATOR);
}

void Fraction::setFraction(int numeratorValue, int denominatorValue) {
    setFraction(0, numeratorValue, denominatorValue);
}

void Fraction::setFraction(int wholeNumber, int numeratorValue, int denominatorValue) {
    int originalNumerator = numerator;
    int originalDenominator = denominator;

    try {
        validateFraction(wholeNumber, numeratorValue, denominatorValue);
        if (wholeNumber > 0) {
            numerator = wholeNumber * denominatorValue + numeratorValue;
    } else {
            numerator = numeratorValue;
    }
        denominator = denominatorValue;
    }
    catch (...) {
        numerator = originalNumerator;
        denominator = originalDenominator;
        throw;
    }
}

string Fraction::toString() const {
    stringstream ss;

    if (denominator == 1) {
        ss << numerator; 
    }
    else {
        int wholeNumberPart = numerator / denominator;
        int remainderNumerator = numerator % denominator;

        if (wholeNumberPart > 0) {
            if (remainderNumerator == 0) {
                ss << wholeNumberPart;
            }
            else {
                ss << wholeNumberPart << " " << remainderNumerator << "/" << denominator;
            }
        }
        else {
            ss << numerator << "/" << denominator;
        }
    }
    return ss.str();
}

int Fraction::getObjectCount() {
    return objectCount;
}

int Fraction::getNumerator() const {
    return numerator;
}

int Fraction::getDenominator() const {
    return denominator;
}

// Operator overload definitions
bool Fraction::operator==(const Fraction& other) const {
    return (numerator * other.denominator) == (other.numerator * denominator);
}

Fraction& Fraction::operator=(const Fraction& other) {
    if (this != &other) {
        numerator = other.numerator;
        denominator = other.denominator;
    }
    return *this;
}

istream& operator>>(istream& is, Fraction& fraction) {
    int num = fraction.numerator;
    int den = fraction.denominator;
    
    char slash;
    is >> num >> slash >> den;
    
    fraction.setFraction(0, num, den);
    return is;
}

ostream& operator<<(ostream& os, const Fraction& fraction) {
    os << fraction.toString();
    return os;
}

void testEqualityOperator() {
    Fraction f1(1, 2);
    Fraction f2(2, 4);
    Fraction f3(3, 4);
    
    cout << "--- Testing == operator ---\n" 
         << f1 << " == " << f2 << " : " << (f1 == f2 ? "true" : "false") << endl
         << f1 << " == " << f3 << " : " << (f1 == f3 ? "true" : "false") << endl;
}

void testAssignmentOperator() {
    Fraction f1(1, 2);
    Fraction f4(3, 4); 
    
    cout << "\n--- Testing = operator ---\n"
         << "Before assignment:\n"
         << "f1: " << f1 << "\n"
         << "f4: " << f4 << "\n";
    
    f4 = f1; 
    
    cout << "After f1 = f4 assignment:\n"
         << "f1: " << f1 << "\n"
         << "f4: " << f4 << "\n";
}

void testOutputOperator() {
    Fraction f6(1, 1);
    Fraction f7(4, 2);
    Fraction f8(3);
    
    cout << "\n--- Testing << operator ---\n"
         << "f6 (" << f6.getNumerator() << "/" << f6.getDenominator() << "): " << f6 << endl
         << "f7 (" << f7.getNumerator() << "/" << f7.getDenominator() << "): " << f7 << endl
         << "f8 (" << f8.getNumerator() << "/" << f8.getDenominator() << "): " << f8 << endl;
}

void testInputOperator() {
    Fraction f5;
    f5.setFraction(4, 5);
    
    cout << "\n--- Testing >> operator (simulated with hardcoded values) ---\n"
         << "f5 (" << f5.getNumerator() << "/" << f5.getDenominator() << "): " << f5 << '\n';
}

void demonstrateOperators() {
    cout << "\n";
    
    testEqualityOperator();
    testAssignmentOperator();
    testOutputOperator();
    testInputOperator();
    
    cout << "\nCurrent Fraction objects in memory: " << Fraction::getObjectCount() << "\n";
}

void printMenu() {
    cout << "\n1. Demonstrate operator overloading\n"
         << "2. Quit\n"
         << "Enter your choice: ";
}

/*OUTPUT TRIALS:
// Menu Output and error handling:
1. Demonstrate operator overloading
2. Quit
Enter your choice: a
Invalid input. Please try again.   

1. Demonstrate operator overloading
2. Quit
Enter your choice: 1
You've demonstrated the operator overloading.

1. Demonstrate operator overloading
2. Quit
Enter your choice: 2

-------------------------------------------------------------------------------------
// Equality operator tests:
1. Demonstrate operator overloading
2. Quit
Enter your choice: 1

--- Testing == operator ---
1/2 == 2/4 : true
1/2 == 3/4 : false

Current Fraction objects in memory: 0

1. Demonstrate operator overloading
2. Quit
Enter your choice: 2

// (seperate test)

1. Demonstrate operator overloading
2. Quit
Enter your choice: 1

--- Testing == operator ---
1/2 == 3/6 : true
1/2 == 3/4 : false

Current Fraction objects in memory: 0

1. Demonstrate operator overloading
2. Quit
Enter your choice: 2

// (seperate test)

1. Demonstrate operator overloading
2. Quit
Enter your choice: 1

--- Testing == operator ---
1/2 == 4/6 : false
1/2 == 3/4 : false

Current Fraction objects in memory: 0

1. Demonstrate operator overloading
2. Quit
Enter your choice: 2

-------------------------------------------------------------------------------------
// Assignment operator tests:

1. Demonstrate operator overloading
2. Quit
Enter your choice: 1

--- Testing == operator ---
1/2 == 2/4 : true
1/2 == 3/4 : false

--- Testing = operator ---
Before assignment:
f1: 1/2
f4: 3/4
After f1 = f4 assignment:
f1: 1/2
f4: 1/2

Current Fraction objects in memory: 0

1. Demonstrate operator overloading
2. Quit
Enter your choice: 2

// (seperate test)

1. Demonstrate operator overloading
2. Quit
Enter your choice: 1

--- Testing == operator ---
1/2 == 2/4 : true
1/2 == 3/4 : false

--- Testing = operator ---
Before assignment:
f1: 4/6
f4: 3/4
After f1 = f4 assignment:
f1: 4/6
f4: 4/6

Current Fraction objects in memory: 0

1. Demonstrate operator overloading
2. Quit
Enter your choice: 2

--------------------------------------------------------------------------------------
// Output operator tests:

1. Demonstrate operator overloading
2. Quit
Enter your choice: 1

--- Testing == operator ---
1/2 == 2/4 : true
1/2 == 3/4 : false

--- Testing = operator ---
Before assignment:
f1: 1/2
f4: 3/4
After f1 = f4 assignment:
f1: 1/2
f4: 1/2

--- Testing << operator ---
f6 (5/2): 2 1/2
f7 (3/8): 3/8
f8 (5/1): 5

Current Fraction objects in memory: 0

1. Demonstrate operator overloading
2. Quit
Enter your choice: 2

// (seperate test)

1. Demonstrate operator overloading
2. Quit
Enter your choice: 1

--- Testing == operator ---
1/2 == 2/4 : true
1/2 == 3/4 : false

--- Testing = operator ---
Before assignment:
f1: 1/2
f4: 3/4
After f1 = f4 assignment:
f1: 1/2
f4: 1/2

--- Testing << operator ---
f6 (7/2): 3 1/2
f7 (5/8): 5/8
f8 (4/1): 4

Current Fraction objects in memory: 0

1. Demonstrate operator overloading
2. Quit
Enter your choice: 2

// (seperate test)

1. Demonstrate operator overloading
2. Quit
Enter your choice: 1

--- Testing == operator ---
1/2 == 2/4 : true
1/2 == 3/4 : false

--- Testing = operator ---
Before assignment:
f1: 1/2
f4: 3/4
After f1 = f4 assignment:
f1: 1/2
f4: 1/2

--- Testing << operator ---
f6 (1/1): 1
f7 (4/2): 2
f8 (3/1): 3

Current Fraction objects in memory: 0

1. Demonstrate operator overloading
2. Quit
Enter your choice: 2

---------------------------------------------------------------------------------------
// Input operator tests:

1. Demonstrate operator overloading
2. Quit
Enter your choice: 1

--- Testing == operator ---
1/2 == 2/4 : true
1/2 == 3/4 : false

--- Testing = operator ---
Before assignment:
f1: 1/2
f4: 3/4
After f1 = f4 assignment:
f1: 1/2
f4: 1/2

--- Testing << operator ---
f6 (1/1): 1
f7 (4/2): 2
f8 (3/1): 3

--- Testing >> operator (simulated with hardcoded values) ---
f5 (3/4): 3/4

Current Fraction objects in memory: 0

1. Demonstrate operator overloading
2. Quit
Enter your choice: 2

// (seperate test)

1. Demonstrate operator overloading
2. Quit
Enter your choice: 1

--- Testing == operator ---
1/2 == 2/4 : true
1/2 == 3/4 : false

--- Testing = operator ---
Before assignment:
f1: 1/2
f4: 3/4
After f1 = f4 assignment:
f1: 1/2
f4: 1/2

--- Testing << operator ---
f6 (1/1): 1
f7 (4/2): 2
f8 (3/1): 3

--- Testing >> operator (simulated with hardcoded values) ---
f5 (4/5): 4/5

Current Fraction objects in memory: 0

1. Demonstrate operator overloading
2. Quit
Enter your choice: 2
*/