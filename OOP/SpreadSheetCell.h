/*
We define the properties that the class *will* have in the header file and implement it later.
*/

#include <string>
class SpreadSheetCell
{
    // this is a private method automatically
    void hiddenMethod();

    public:
        SpreadSheetCell(); // default constructor
        SpreadSheetCell(double initialValue); // constructor with initial double value
        SpreadSheetCell(std::string initialStringValue); // constructor with initial string value
        SpreadSheetCell(const SpreadSheetCell& src); // copy constructor
        ~SpreadSheetCell(); // destructor
        SpreadSheetCell& operator=(const SpreadSheetCell& rhs); // assignment operator overload
        void setValue(double inValue);
        double getValue();
        void setString(std::string inString);
        const SpreadSheetCell add(const SpreadSheetCell &cell) const;
        const SpreadSheetCell operator+(const SpreadSheetCell &cell) const;
        std::string getString();
    protected:
        double value_;
};