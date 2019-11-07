/*
 *  amb512P4.cpp
 *
 *  COSC 051 Summer 2017
 *  Georgetown Summer College Course
 *  Project #4
 *
 */

# include <iostream>
# include <iomanip>
# include <math.h>
# include <fstream>
# include <string>
# include <sstream>
# include <vector>
# include <cstdlib>

using namespace std;

//DEFINE GLOBAL CONSTANTS

// bulk entry
const int MAXTEMPC = 60, MINTEMPC = -100, MAXTEMPF = 140, MINTEMPF = -148, MINRH = 0, MAXRH = 1;
const double A = 17.27, B = 237.7, COEF_CELSIUS = (5.00 / 9.00), CONVERSION_NUM = 32,
COEF_FARENHEIT = (9.00 / 5.00);
const int JANUARY = 1, FEBRUARY = 2, MARCH = 3, APRIL = 4, MAY = 5, JUNE = 6, JULY = 7, AUGUST = 8,
SEPTEMBER = 9, OCTOBER = 10, NOVEMBER = 11, DECEMBER = 12;
const int MAX31DAY = 31;
const int MAX30DAY = 30;
const int MINDAY = 1;
const int MAX29DAY = 29;
const int SIZE = 1000;
const int MAXYEAR = 2017;
const int MINYEAR = 1800;
const char CH = '/';
const char ZERO = '0';
const char BLANK = ' ';
const char F = 'F', C = 'C';
const int ONE = 1;

const int NIL = 0;

//define global constant numbers

// displayMenu
const int MAX_MENU_TRIES = 10;

/***************************************************************************************
 *                                                                                     *
 *                                   Project #4                                        *
 *                            class Weather declaraion                                 *
 *                                                                                     *
 ***************************************************************************************/

class Weather
{
    // overloaded stream insertion operator
    // outputs all values for this object on one line (similar to the format of the input file)
    friend ostream& operator<<( ostream &os, const Weather &rhsObj );
    
    // overloaded stream extraction operator
    // in one statement extracts all values from a stream and updates the data member values
    friend istream& operator>>( istream &is, Weather &rhsObj );
    
private:
    int month, day, year;
    double relativeHumidity, airTemp;
    char tempUnits;
    string name;
    
public:
    
    // default constructor
    Weather();
    // constructor with parameters
    Weather( int m, int d, int y, double rH, double aT, char tU, string n );
    // copy constructor
    Weather( const Weather & );
    // destructor, the destructor for this class does not have much (really anything) to
    // do, but it can be informative to put some diagnostic output during early
    // stages of development
    ~Weather();
    
    // overloaded assignment operator
    Weather& operator=( const Weather & );
    
    // method to calculate the dew point for this Weather object
    double getDewPoint() const;
    // method to validate the date
    void isValidDate(bool &answer, string &message) const;
    // method to validate the relative humidity
    void isValidRH(bool &answer, string &message) const;
    // method to validate the air temperature
    void isValidTemp(bool &answer, string &message) const;
    // method to validate the units
    void isValidUnits(bool &answer, string &message) const;
    // method to return true if all validation tests are successful
    // also returns a string with consolidated error message from
    // all other validation tests
    void isValidRecord(bool &answer, string &message) const;
    
    // basic accessor functions (could be implemented inside (inline) or outside the declaration
    int getMonth() const { return month; }
    int getDay() const { return day; }
    int getYear() const { return year; }
    double getRelativeHumidity() const { return relativeHumidity; }
    double getAirTemp() const { return airTemp; }
    char getTempUnits() const { return tempUnits; }
    string getName() const { return name; }
    
    // basic mutator functions (could be implemented inside (inline) or outside the declaration
    void setMonth(int m) { month = m; }
    void setDay(int d) { day = d; }
    void setYear(int y) { year = y; }
    void setRelativeHumidity(double rH) { relativeHumidity = rH; }
    void setAirTemp(double aT) { airTemp = aT; }
    void setTempUnits(char tU) { tempUnits = tU; }
    void setName(string n) { name = n; }
    
}; //END declaration for class Weather

//define prototypes
char displayMenu();

bool uploadFile(string fName, vector<Weather> &readings);

void allDetails(const vector<Weather> &readings);

void dateDetails(const vector<Weather> &readings);

void summaryByScale(const vector<Weather> &readings);

//default constructor
Weather::Weather()
{
    month = 0;
    day = 0;
    year = 0;
    relativeHumidity = 0;
    airTemp = 0;
    tempUnits = '?';
    name = "";
}

//constructor with parameters
Weather::Weather( int m, int d, int y, double rH, double aT, char tU, string n )
{
    month = m;
    day = d;
    year = y;
    relativeHumidity = rH;
    airTemp = aT;
    tempUnits = tU;
    name = n;
}

//copy constructor
Weather::Weather( const Weather &rhsObj )
{
    month = rhsObj.month;
    day = rhsObj.day;
    year = rhsObj.year;
    relativeHumidity = rhsObj.relativeHumidity;
    airTemp = rhsObj.airTemp;
    tempUnits = rhsObj.tempUnits;
    name = rhsObj.name;
}

//destructor
Weather::~Weather()
{
    
}

//overloaded assignment operator
Weather& Weather::operator=( const Weather &rhsObj )
{
    if (this != &rhsObj)
    {
        month = rhsObj.month;
        day = rhsObj.day;
        year = rhsObj.year;
        relativeHumidity = rhsObj.relativeHumidity;
        airTemp = rhsObj.airTemp;
        tempUnits = rhsObj.tempUnits;
        name = rhsObj.name;
    }
    
    return *this;
}

// initiate code with int main
int main(int argc, const char * argv[])
{
    //define local variables
    bool result = true;
    char menuSelection = '?';
    
    string fName = "";
    vector<Weather> readings;
    
    while (result == true)
    {
        // move into options
        menuSelection = displayMenu();
        switch (menuSelection)
        {
            case 'U':
                cout << "Calling function uploadFile(" << fName << " )...\n";
                cout << "There are " << readings.size() << " elements in the vector(s).\n";
                result = uploadFile(fName, readings);
                
                if ( result == false)
                {
                    cout << "Control returned from uploadFile unsuccessfully. \n";
                    cout << "There are " << readings.size() << " elements in the vector(s).\n";
                }
                else
                {
                    cout << "Control returned from uploadFile successfully. \n";
                    cout << "There are " << readings.size() << " elements in the vector(s).\n";
                }
                break;
                
                
                
            case 'A':
                cout << "Calling function allDetails(" << fName << " )...\n";
                cout << "There are " << readings.size() << " elements in the vector(s).\n";
                allDetails(readings);
                cout << "Control returned from allDetails. \n";
                cout << "There are " << readings.size() << " elements in the vector(s).\n";
                break;
                
                
                
            case 'D':
                cout << "Calling function dateDetails(" << fName << " )...\n";
                cout << "There are " << readings.size() << " elements in the vector(s).\n";
                dateDetails(readings);
                cout << "Control returned from dateDetails. \n";
                cout << "There are " << readings.size() << " elements in the vector(s).\n";
                break;
                
                
                
            case 'S':
                cout << "Calling function SummaryByScale(" << fName << " )...\n";
                cout << "There are " << readings.size() << " elements in the vector(s).\n";
                summaryByScale(readings);
                cout << "Control returned from SummaryByScale. \n";
                cout << "There are " << readings.size() << " elements in the vector(s).\n";
                break;
                
                
                
            case 'C':
                cout << "There are " << readings.size() << " elements in the vector(s).\n";
                cout << "Clearing all data...\n";
                readings.clear();
                cout << "There are " << readings.size() << " elements in the vector(s).\n";
                break;
                
                
                
            case 'Q':
                cout << "Exiting program. Have a nice day!\n";
                result = false;
                break;
        }
    }
    return 0;
}


/****************************************************************************
 *                                                                          *
 *                       function displayMenu                               *
 *                                                                          *
 ****************************************************************************/

char displayMenu()
{
    //print menu
    cout << "Entered function displayMenu..." << endl;
    cout << endl;
    int loopCount = 0;
    char menuSelection = '?';
    
    do
    {
        cout << setw(45) << "Blue Ridge Weather Analytics" << endl;
        cout << setw(55) << "This application calculates the dew point for given\n";
        cout << setw(55) << "relative humidity and air temperature values.\n";
        cout << endl;
        cout << right << setw(55) << " upload a meteorologist's data file     U\n";
        cout << right << setw(55) << " display details (all loaded data)     A\n";
        cout << right << setw(55) << " list details for a specific date (all matches)     D\n";
        cout << right << setw(55) << " display summary - order by temperature scale     S\n";
        cout << right << setw(55) << " clear all data     C\n";
        cout << right << setw(55) << " quit     Q\n";
        cout << endl;
        cout << "Please enter a letter to choose an option from above: ";
        cout << endl;
        
        //input menu
        cin >> menuSelection;
        cin.ignore(500, '\n');
        loopCount++;
        menuSelection = toupper(menuSelection);
        
        if ( menuSelection != 'U' && menuSelection != 'A' && menuSelection != 'D'
            && menuSelection != 'M' && menuSelection != 'S'
            && menuSelection != 'C' && menuSelection != 'Q')
        {
            cout << menuSelection << " is not a valid menu option... please try again.\n";
            cout << endl;
        }
        
    } while ( menuSelection != 'U' && menuSelection != 'A' && menuSelection != 'D'
             && menuSelection != 'M' && menuSelection != 'S'
             && menuSelection != 'C' && menuSelection != 'Q' && loopCount <= MAX_MENU_TRIES);
    
    if ( menuSelection != 'U' && menuSelection != 'A' && menuSelection != 'D'
        && menuSelection != 'M' && menuSelection != 'S'
        && menuSelection != 'C' && menuSelection != 'Q' && loopCount >= MAX_MENU_TRIES)
    {
        cout << MAX_MENU_TRIES+1 << " attempts to select a valid value is too many tries! \n";
        cout << "WARNING: " << menuSelection << " is not a valid option. \n";
        cout << "Control is returning to the main function...\n" << endl;
    }
    cout << "Exiting function displayMenu. \n";
    return menuSelection;
} // END function displayMenu




/****************************************************************************
 *                                                                          *
 *                        function uploadFile                               *
 *                                                                          *
 ****************************************************************************/

bool uploadFile(string fName, vector<Weather> &readings)
{
    //define local variables
    int numOfFarenheit = 0;
    int numOfCelsius = 0;
    int numOfInvalid = 0;
    int m = 0, d = 0, y = 0;
    double farenheitSum = 0.00;
    double celsiusSum = 0.00;
    double avgFarenheit = 0.00;
    double avgCelsius = 0.00;
    string date = "";
    string name = "";
    double sdCelsius = 0.00;
    double sdFarenheit = 0.00;
    int counter = 0;
    unsigned long initialSize = 0;
    
    string blankString = " ";
    
    fName = "";
    ifstream inFile;
    string oneLine = "";
    
    bool dateValid = true;
    int recordCount = 0;
    
    bool tempValid = true;
    
    bool tempUnitValid = true;
    bool rhValid = true;
    
    bool record = true;
    
    bool result = true;
    
    double relativeHumidity = 0.00, temperature = 0.00,
    dewPointTemperature = 0.00, f_T_RH = 0.00;
    bool farenheitConversionCheck = false;
    char tempUnit = '?';
    
    string message = "";
    string allMessages = "";
    Weather w1;
    
    // C:/Users/Alexander/Desktop/GeorgetownCompSci/Homework&Projects/P3/P3pascal.prn
    // C:/Users/Alexander/Desktop/GeorgetownCompSci/Homework&Projects/P2/dataFileTest03.dat
    
    cout << "Please enter the full path name of the data file to load: ";
    
    cin >> fName;
    
    inFile.open(fName.c_str());
    
    if(!inFile) //if file didn't open
    {
        cout << "The file: " << fName << " failed to open :-( " << endl;
        cout << "The program will now return to the menu..." << endl;
        result = false;
        return result;
    }
    else //proceed
    {
        //read file
        initialSize = readings.size();
        
        getline(inFile, oneLine);
        cout << "File information: \n";
        
        //output heading
        cout << "-------------------------------------------------------------------";
        cout << "-------------------------------------------------------------------" << endl;
        cout << setw(7) << "Date";
        cout << setw(25) << "Relative Humidity";
        cout << setw(20) << "Temperature";
        cout << setw(22) << "Dew Point";
        cout << setw(35) << "Meteorologist name" << endl;
        cout << "-------------------------------------------------------------------";
        cout << "-------------------------------------------------------------------" << endl;
        
        while ( inFile >> w1)
        {
            //reset variables
            tempValid = true;
            tempUnitValid = true;
            rhValid = true;
            dateValid = true;
            record = true;
            
            message = "";
            allMessages = "";
            
            //check validity and print error messages
            w1.isValidRecord(record, message);
            
            if (record)
            {
                readings.push_back(w1);
                
                if (w1.getTempUnits() == F)
                {
                    numOfFarenheit++;
                    farenheitSum = farenheitSum + w1.getAirTemp();
                }
                else
                {
                    numOfCelsius++;
                    celsiusSum = celsiusSum + w1.getAirTemp();
                }
                
                cout << w1;
                recordCount++;
                
            }
            else
            {
                cout << w1;
                numOfInvalid++;
            }
        }
        //final calculations
        avgFarenheit = (farenheitSum / numOfFarenheit);
        avgCelsius = (celsiusSum / numOfCelsius);
        
        //calculate standard deviation
        double sdNumberF = 0.00;
        double sdNumberC = 0.00;
        double midF = 0.00;
        double midC = 0.00;
        int fCounter = 0;
        int cCounter = 0;
        
        for (unsigned long i = initialSize; i < readings.size(); i++)
        {
            if (readings[i].getTempUnits() == F)
            {
                midF = readings[i].getAirTemp() - avgFarenheit;
                sdNumberF += pow(midF, 2);
                fCounter++;
            }
            else if (readings[i].getTempUnits() == C)
            {
                midC = readings[i].getAirTemp() - avgCelsius;
                sdNumberC += pow(midC, 2);
                cCounter++;
            }
        }
        
        sdFarenheit = sqrt(sdNumberF / (fCounter - ONE));
        sdCelsius = sqrt(sdNumberC / (cCounter - ONE));
        
        
        //final calculations output
        cout << "The total records in file: " << recordCount << endl;
        cout << numOfFarenheit << " Farenheit readings, with average air temp = " << avgFarenheit;
        cout << " and standard deviation = " << sdFarenheit << endl;
        cout << numOfCelsius << " Celsius readings, with average air temp = " << avgCelsius;
        cout << " and standard deviation = " << sdCelsius << endl;
        cout << numOfInvalid << " readings with invalid data.";
        cout << endl;
        
        if (readings.size() > initialSize)
        {
            cout << "NOTE: Data file successfully loaded. \n";
        }
        else if (readings.size() <= initialSize)
        {
            cout << "NOTE: Data file not loaded. \n";
        }
        inFile.close();
    } //end else block paired with if(!inFile)
    return result;
}


/****************************************************************************
 *                                                                          *
 *                        function allDetails                               *
 *                                                                          *
 ****************************************************************************/

void allDetails(const vector<Weather> &readings)
{
    if ( readings.size() > NIL)
    {
        cout << "Entered function allDetails, there are ";
        cout << readings.size() << " elements in the vector(s)." << endl;
        
        //output heading
        cout << "-------------------------------------------------------------------";
        cout << "-------------------------------------------------------------------" << endl;
        cout << setw(7) << "Date";
        cout << setw(25) << "Relative Humidity";
        cout << setw(20) << "Temperature";
        cout << setw(22) << "Dew Point";
        cout << setw(35) << "Meteorologist name" << endl;
        cout << "-------------------------------------------------------------------";
        cout << "-------------------------------------------------------------------" << endl;
        
        //local variables
        int i = 0;
        int max = 0;
        double dewPointTemperature = 0.0;
        max = readings.size();
        double farenheitSum = 0.00;
        double celsiusSum = 0.00;
        double avgFarenheit = 0.00;
        double avgCelsius = 0.00;
        int numOfFarenheit = 0;
        int numOfCelsius = 0;
        
        
        for (i = 0; i < max; i++)
        {
            //output date
            cout << setfill(ZERO);
            cout << setw(2) << readings[i].getMonth();
            cout << setfill(BLANK);
            
            cout << setw(1) << CH;
            
            cout << setfill(ZERO);
            cout << setw(2) << readings[i].getDay();
            cout << setfill(BLANK);
            
            cout << setw(1) << CH;
            
            cout << setfill(ZERO);
            cout << setw(4) << readings[i].getYear();
            cout << setfill(BLANK);
            
            //output relative humidity
            cout << setw(15) << readings[i].getRelativeHumidity();
            
            //output air temperature
            cout << setw(23) << readings[i].getAirTemp();
            
            //output temperature unit
            cout << setw(3) << readings[i].getTempUnits();
            
            //output dew point
            dewPointTemperature = readings[i].getDewPoint();
            cout << setw(19) << dewPointTemperature;
            
            //output temp unit
            cout << setw(3) << readings[i].getTempUnits();
            
            //output name
            cout << right << setw(25) << readings[i].getName();
            
            //add to f and c counters and sums
            if ( readings[i].getTempUnits() == F)
            {
                numOfFarenheit++;
                farenheitSum = farenheitSum + readings[i].getAirTemp();
            }
            else if ( readings[i].getTempUnits() == C)
            {
                numOfCelsius++;
                celsiusSum = celsiusSum + readings[i].getAirTemp();
            }
            cout << endl;
        }
        
        cout << "-------------------------------------------------------------------";
        cout << "-------------------------------------------------------------------" << endl;
        
        //final calculations
        avgFarenheit = (farenheitSum / numOfFarenheit);
        avgCelsius = (celsiusSum / numOfCelsius);
        
        //final calculations output
        cout << endl;
        cout << "The total records in file: " << max << endl;
        cout << numOfFarenheit << " Farenheit readings, with average air temp = " << avgFarenheit;
        cout << endl;
        cout << numOfCelsius << " Celsius readings, with average air temp = " << avgCelsius << endl;
        
        cout << "Exiting function allDetails." << endl;
    }
    else
    {
        cout << "WARNING: You must first upload a data file!\n";
    }
    return;
} // END function allDetails


/****************************************************************************
 *                                                                          *
 *                        function dateDetails                              *
 *                                                                          *
 ****************************************************************************/

void dateDetails(const vector<Weather> &readings)
{
    if (readings.size() > NIL)
    {
        //define local variables
        string inputtedDate = "";
        int mm = 0, dd = 0, yyyy = 0;
        string blankString = " ";
        int i = 0;
        stringstream date;
        int counter = 0;
        
        bool monthValid = true;
        bool dayValid = true;
        bool yearValid = true;
        bool valid = true;
        bool februaryCheck = false;
        bool thirtyOneMonth = false;
        bool dateValid = true;
        
        double farenheitSum = 0.00;
        double celsiusSum = 0.00;
        double avgFarenheit = 0.00;
        double avgCelsius = 0.00;
        int numOfFarenheit = 0;
        int numOfCelsius = 0;
        double dewPointTemperature = 0.0;
        
        //initialize
        cout << "Please enter a specific date to display using the format mm/dd/yyyy: ";
        cin >> inputtedDate;
        
        //split into different parts
        date << inputtedDate;
        
        getline(date, blankString, CH);
        stringstream monthStream(blankString);
        monthStream >> mm;
        
        getline(date, blankString, CH);
        stringstream dayStream(blankString);
        dayStream >> dd;
        
        getline(date, blankString);
        stringstream yearStream(blankString);
        yearStream >> yyyy;
        
        //VALIDATION CHECKS:
        
        //month check
        if (mm == FEBRUARY)
        {
            februaryCheck = true;
        }
        else if (mm == JANUARY || mm == MARCH || mm == MAY ||
                 mm == JULY || mm == AUGUST || mm == OCTOBER || mm == DECEMBER )
        {
            thirtyOneMonth = true;
        }
        else if (mm < JANUARY || mm > DECEMBER )
        {
            monthValid = false;
        }
        
        //day check
        if (februaryCheck == true)
        {
            if (dd > MAX29DAY || dd < MINDAY)
            {
                dayValid = false;
            }
        }
        else if (thirtyOneMonth == true)
        {
            if (dd > MAX31DAY || dd < MINDAY)
            {
                dayValid = false;
            }
        }
        else if (thirtyOneMonth == false)
        {
            if (dd > MAX30DAY || dd < MINDAY)
            {
                dayValid = false;
            }
        }
        
        //year check
        if (yyyy > MAXYEAR || yyyy < MINYEAR)
        {
            yearValid = false;
        }
        
        //check valid false
        if (monthValid == false || dayValid == false || yearValid == false )
        {
            dateValid = false;
        }
        
        if ( dateValid == true)
        {
            //output heading
            cout << "-------------------------------------------------------------------";
            cout << "-------------------------------------------------------------------" << endl;
            cout << setw(7) << "Date";
            cout << setw(25) << "Relative Humidity";
            cout << setw(20) << "Temperature";
            cout << setw(22) << "Dew Point";
            cout << setw(35) << "Meteorologist name" << endl;
            cout << "-------------------------------------------------------------------";
            cout << "-------------------------------------------------------------------" << endl;
            
            for (i = 0; i < readings.size(); i++)
            {
                if ( readings[i].getMonth() == mm &&
                    readings[i].getDay() == dd && readings[i].getYear() == yyyy)
                {
                    //output date
                    cout << setfill('0');
                    cout << setw(2) << mm;
                    cout << setfill(BLANK);
                    
                    cout << setw(1) << CH;
                    
                    cout << setfill('0');
                    cout << setw(2) << dd;
                    cout << setfill(BLANK);
                    
                    cout << setw(1) << CH;
                    
                    cout << setfill('0');
                    cout << setw(4) << yyyy;
                    cout << setfill(BLANK);
                    
                    //add to record counter
                    counter++;
                    
                    //output relative humidity
                    cout << setw(15) << readings[i].getRelativeHumidity();
                    
                    //output air temperature
                    cout << setw(23) << readings[i].getAirTemp();
                    
                    //output temperature unit
                    cout << setw(3) << readings[i].getTempUnits();
                    
                    //output dew point
                    dewPointTemperature = readings[i].getDewPoint();
                    cout << setw(19) << dewPointTemperature;
                    
                    //output temp unit
                    cout << setw(3) << readings[i].getTempUnits();
                    
                    //output name
                    cout << setw(20) << readings[i].getName();
                    
                    //add to f and c counters and sums
                    if ( readings[i].getTempUnits() == F)
                    {
                        numOfFarenheit++;
                        farenheitSum = farenheitSum + readings[i].getAirTemp();
                    }
                    else if ( readings[i].getTempUnits() == C)
                    {
                        numOfCelsius++;
                        celsiusSum = celsiusSum + readings[i].getAirTemp();
                    }
                    cout << endl << endl;
                }
            }
            //final calculations
            avgFarenheit = (farenheitSum / numOfFarenheit);
            avgCelsius = (celsiusSum / numOfCelsius);
            
            if (counter > NIL)
            {
                cout << "Total records in file: " << counter << endl;
                if (numOfFarenheit != NIL)
                {
                    cout << numOfFarenheit << " Farenheit readings, ";
                    cout << "with average air temp = " << avgFarenheit;
                }
                else
                    cout << numOfFarenheit << " Farenheit readings, with average air temp = " << NIL;
                cout << endl;
                if (numOfCelsius != NIL)
                    cout << numOfCelsius << " Celsius readings, with average air temp = " << avgCelsius;
                else
                    cout << numOfCelsius << " Farenheit readings, with average air temp = " << NIL;
                cout << endl;
            }
            else
            {
                cout << "There were no records matching date " << inputtedDate << endl;
            }
        }
        else
        {
            cout << "This date is invalid. Please try again!\n";
        }
    }
    else
    {
        cout << "WARNING: You must first upload a data file!\n";
    }
    return;
}



/****************************************************************************
 *                                                                          *
 *                       function summaryByScale                            *
 *                                                                          *
 ****************************************************************************/


void summaryByScale(const vector<Weather> &readings)
{
    if (readings.size() > NIL)
    {
        //local variables
        double rhSumF = 0.00;
        double rhSumC = 0.00;
        double tempSumF = 0.00;
        double tempSumC = 0.00;
        double dpSumF = 0.00;
        double dpSumC = 0.00;
        
        double rhAvgF = 0.00;
        double rhAvgC = 0.00;
        double tempAvgF = 0.00;
        double tempAvgC = 0.00;
        double dpAvgF = 0.00;
        double dpAvgC = 0.00;
        
        int fCounter = 0;
        int cCounter = 0;
        int i = 0;
        double dewPointTemperatureF = 0.00;
        double dewPointTemperatureC = 0.00;
        
        //output heading
        cout << "-------------------------------------------------------------------";
        cout << "-------------------------------------------------------------------" << endl;
        cout << setw(80) << "Average Readings by Temperature Scale" << endl;
        cout << endl;
        cout << setw(50) << "Relative Humidity";
        cout << setw(17) << "Temperature";
        cout << setw(17) << "Dew Point" << endl;
        cout << "-------------------------------------------------------------------";
        cout << "-------------------------------------------------------------------" << endl;
        
        for (i = 0; i < readings.size(); i++)
        {
            if ( readings[i].getTempUnits() == F)
            {
                //counter
                fCounter++;
                
                //rh
                rhSumF += readings[i].getRelativeHumidity();
                
                //air temp
                tempSumF += readings[i].getAirTemp();
                
                //dew point
                dewPointTemperatureF = readings[i].getDewPoint();
                dpSumF += dewPointTemperatureF;
            }
            else if ( readings[i].getTempUnits() == C)
            {
                //counter
                cCounter++;
                
                //rh
                rhSumC += readings[i].getRelativeHumidity();
                
                //air temp
                tempSumC += readings[i].getAirTemp();
                
                //dew point
                dewPointTemperatureC = readings[i].getDewPoint();
                dpSumC += dewPointTemperatureC;
            }
        }
        //rh averages
        rhAvgF = rhSumF / fCounter;
        rhAvgC = rhSumC / cCounter;
        
        //temp averages
        tempAvgF = tempSumF / fCounter;
        tempAvgC = tempSumC / cCounter;
        
        //dewpoint averages
        dpAvgF = dpSumF / fCounter;
        dpAvgC = dpSumC / cCounter;
        
        //output all F
        cout << setw(45) << rhAvgF;
        cout << setw(19) << tempAvgF;
        cout << setw(3) << F;
        cout << setw(14) << dpAvgF;
        cout << setw(3) << F << endl;
        
        //output all C
        cout << setw(45) << rhAvgC;
        cout << setw(19) << tempAvgC;
        cout << setw(3) << C;
        cout << setw(14) << dpAvgC;
        cout << setw(3) << C << endl;
        
        cout << "-------------------------------------------------------------------";
        cout << "-------------------------------------------------------------------" << endl;
    }
    else
    {
        cout << "WARNING: You must first upload a data file!\n";
    }
    return;
}


// VALIDATION CHECKS

/****************************************************************************
 *                                                                          *
 *                       function isValidDate                               *
 *                                                                          *
 ****************************************************************************/

void Weather::isValidDate(bool &answer, string &message) const
{
    answer = true;
    bool monthValid = true;
    bool dayValid = true;
    bool februaryCheck = false;
    bool thirtyOneMonth = false;
    bool yearValid = true;
    message = "";
    
    //month check
    if (month == FEBRUARY)
    {
        februaryCheck = true;
    }
    else if (month == JANUARY || month == MARCH || month == MAY ||
             month == JULY || month == AUGUST || month == OCTOBER || month == DECEMBER )
    {
        thirtyOneMonth = true;
    }
    else if (month < JANUARY || month > DECEMBER )
    {
        monthValid = false;
        answer = false;
    }
    
    //day check
    if (februaryCheck == true)
    {
        if (day > MAX29DAY || day < MINDAY)
        {
            dayValid = false;
            answer = false;
        }
    }
    else if (thirtyOneMonth == true)
    {
        if (day > MAX31DAY || day < MINDAY)
        {
            dayValid = false;
            answer = false;
        }
    }
    else if (thirtyOneMonth == false)
    {
        if (day > MAX30DAY || day < MINDAY)
        {
            dayValid = false;
            answer = false;
        }
    }
    
    //year check
    if (year > MAXYEAR || year < MINYEAR)
    {
        yearValid = false;
        answer = false;
    }
    
    //store error messages
    if ( monthValid == false)
    {
        message += "    The month is not valid.\n";
    }
    
    if ( dayValid == false)
    {
        message += "    The day is not valid.\n";
    }
    
    if ( yearValid == false)
    {
        message += "    The year is not valid.\n";
    }
}




/****************************************************************************
 *                                                                          *
 *                       function isValidUnits                              *
 *                                                                          *
 ****************************************************************************/

void Weather::isValidUnits(bool &answer, string &message) const
{
    answer = true;
    message = "";
    
    if ( tempUnits == F || tempUnits == C )
    {
        answer = true;
    }
    else
    {
        answer = false;
        message += "    The temperature unit is not valid.\n";
    }
} // END function isValidScale




/****************************************************************************
 *                                                                          *
 *                       function isValidTemp                               *
 *                                                                          *
 ****************************************************************************/

void Weather::isValidTemp(bool &answer, string &message) const
{
    answer = true;
    message = "";
    
    if ( tempUnits == F )
    {
        if (airTemp > MAXTEMPF || airTemp < MINTEMPF)
        {
            answer = false;
            message += "    The temperature is not valid.\n";
        }
    }
    else if (tempUnits == C)
    {
        if (airTemp > MAXTEMPC || airTemp < MINTEMPC)
        {
            answer = false;
            message += "    The temperature is not valid.\n";
        }
    }
}




/****************************************************************************
 *                                                                          *
 *                       function isValidRH                                 *
 *                                                                          *
 ****************************************************************************/


void Weather::isValidRH(bool &answer, string &message) const
{
    answer = true;
    message = "";
    
    //relative humidity check
    if ( relativeHumidity > MAXRH || relativeHumidity <= MINRH)
    {
        answer = false;
        message += "    The relative humidity is not valid.\n";
    }
    return;
}


/****************************************************************************
 *                                                                          *
 *                       function getDewPoint                               *
 *                                                                          *
 ****************************************************************************/

double Weather::getDewPoint() const
{
    bool farenheitConversionCheck = false;
    double f_T_RH = 0.00;
    double dewPointTemperature = 0.00;
    double convertedTemp = this->airTemp;
    double reconvertedTemp = 0.00;
    
    //dew point temp check
    if (this->tempUnits == F)
    {
        farenheitConversionCheck = true;
    }
    //convert Farenheit to Celsius if required.
    if (farenheitConversionCheck == true)
    {
        convertedTemp = COEF_CELSIUS * (this->airTemp - CONVERSION_NUM);
    }
    
    //calculate f(T, RH), part of relative humidity equation.
    f_T_RH = ((A * convertedTemp) / (B + convertedTemp)) + log(this->relativeHumidity);
    
    //calculate dew point temperature
    dewPointTemperature = (B * (f_T_RH) / (A - f_T_RH));
    
    //check if initially Farenheit and change dew point to Farenheit if so
    if (farenheitConversionCheck == true)
        dewPointTemperature = (COEF_FARENHEIT * dewPointTemperature) + CONVERSION_NUM;
    
    return dewPointTemperature;
}



/****************************************************************************
 *                                                                          *
 *               overloaded stream insertion operator                       *
 *                                                                          *
 ****************************************************************************/
ostream& operator<<( ostream &os, const Weather &rhsObj )
{
    os << right << setfill('0');
    os << setw(2) << rhsObj.month;
    os << setfill(BLANK);
    
    os << setw(1) << CH;
    
    os << setfill('0');
    os << setw(2) << rhsObj.day;
    os << setfill(BLANK);
    
    os << setw(1) << CH;
    
    os << setfill('0');
    os << setw(4) << rhsObj.year;
    os << setfill(BLANK);
    
    //output relative humidity
    os << setw(15) << rhsObj.relativeHumidity;
    
    //output air temperature
    os << setw(23) << rhsObj.airTemp;
    
    //output temperature unit
    os << setw(3) << rhsObj.tempUnits;
    
    //check date
    bool dateValid;
    string dateInvalid = "";
    rhsObj.isValidDate(dateValid, dateInvalid);
    
    //check rh
    bool rhValid;
    string rhInvalid = "";
    rhsObj.isValidRH(rhValid, rhInvalid);
    
    //check tempunit
    bool tempUnitValid;
    string tuInvalid = "";
    rhsObj.isValidUnits(tempUnitValid, tuInvalid);
    
    //check temperature
    bool tempValid;
    string tempInvalid = "";
    rhsObj.isValidTemp(tempValid, tempInvalid);
    
    //store validated data if true
    bool record;
    string recInvalid = "";
    rhsObj.isValidRecord(record, recInvalid);
    
    if (rhValid == true && tempUnitValid == true && tempValid == true)
    {
        os << fixed << setprecision(2);
        os << setw(19) << rhsObj.getDewPoint();
        os << setw(3) << rhsObj.tempUnits;
        os << setw(23) << rhsObj.name << endl;
    }
    else
    {
        os << setw(22) << "Check input!";
        os << setw(23) << rhsObj.name << endl;
        os << recInvalid;
    }
    return os;
}




/****************************************************************************
 *                                                                          *
 *               overloaded stream extraction operator                      *
 *                                                                          *
 ****************************************************************************/
istream& operator>>( istream &is, Weather &rhsObj )
{
    string date = "";
    string blankString = "";
    string tempUnits = "";
    
    //read
    is >> date >> rhsObj.relativeHumidity >> rhsObj.airTemp >> tempUnits && getline(is, rhsObj.name);
    
    //separate date into dd/mm/yyyy
    stringstream dateString;
    dateString << date;
    
    getline(dateString, blankString, CH);
    stringstream monthStream(blankString);
    monthStream >> rhsObj.month;
    
    getline(dateString, blankString, CH);
    stringstream dayStream(blankString);
    dayStream >> rhsObj.day;
    
    getline(dateString, blankString);
    stringstream yearStream(blankString);
    yearStream >> rhsObj.year;
    
    //turn tempunit to upper case and read only first character
    rhsObj.tempUnits = toupper(tempUnits[0]);
    
    return is;
}




/****************************************************************************
 *                                                                          *
 *                       function isValidRecord                             *
 *                                                                          *
 ****************************************************************************/

void Weather::isValidRecord(bool &answer, string &message) const
{
    answer = true;
    bool dateValid = true;
    bool rhValid = true;
    bool tempUnitValid = true;
    bool tempValid = true;
    
    string dateInvalid = "";
    string rhInvalid = "";
    string tempInvalid = "";
    string recInvalid = "";
    string tuInvalid = "";
    message = "";
    
    //check date
    isValidDate(dateValid, dateInvalid);
    
    //check rh
    isValidRH(rhValid, rhInvalid);
    
    //check tempunit
    isValidUnits(tempUnitValid, tuInvalid);
    
    //check temperature
    isValidTemp(tempValid, tempInvalid);
    
    if (dateValid == true && rhValid == true && tempUnitValid == true && tempValid == true)
    {
        answer = true;
    }
    else
    {
        answer = false;
        message += dateInvalid + tuInvalid + tempInvalid +  rhInvalid;
    }
}

