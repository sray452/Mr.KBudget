#include <iostream>
#include <fstream> // to use ifstream
#include <sstream> // to use istringstream
using namespace std;

// Function prototype to open file
bool openFileIn(ifstream &, string);
// populate (initialize the two arrays (days[] and prices[])
void populateData(ifstream &);
// extract words
string extractDay(string line);
double extractPrice(string line);
// overloaded functions to display Array elements
void displayArray(string [], int);
void displayArray(double [], int);

// New functions, calculate sum total and write it to total.txt file
double totalBudget(double []);
void textFileFunction(double sumTotal);

// global variables to hold and process data for analysis
const int SIZE = 7;
string days[SIZE];
double prices[SIZE];

int main()
{
    double sumTotal;

    // declare input file stream to store data from file
    ifstream dataFile;
	if (openFileIn(dataFile, "budget.txt")) // if budget.txt file exists and opens
    {
        // store data from the text file to days and prices
    	populateData(dataFile);

        // checking if days and prices have been populated
    	displayArray(days, SIZE);  // you may want to delete it
        displayArray(prices, SIZE); // you may want to delete it

    	dataFile.close();
	}
	else {
       cout << "File open error!" << endl;
	}

	// Calling totalBudget function and assigning sumTotal variable to the returned result
	sumTotal = totalBudget(prices);

	// Display the sum total on the console
	cout << "The sum total of Mr. K's budget is $" << sumTotal << "." << endl;

	// Call the textFileFunction to write the sum total of the budget to the total.txt file
	textFileFunction(sumTotal);

	return 0;
}

/*
 * This function open a file and returns true if good
 */
bool openFileIn(ifstream &file, string fileName)
{
    file.open(fileName);
    if (file.fail())
    {
        return false;
    }
    else
    {
        return true;
    }
}

/*
 * This function takes a stream of string as a reference to the
 * file, process each line of the file by extracting substring,
 * and store data to days[] and prices[]
*/
void populateData(ifstream &file)
{
    string line;
    int index = 0;
    while (!file.eof())
    {
        getline(file, line);
        string day = extractDay(line);
        double price = extractPrice (line);
        days[index] = day;  // store day to the global array days[]
        prices[index] = price;// store price to the global array prices[]
        index++;
    }
}

/*
 * This function takes a string as a parameter with two words
 * The first word is a day of week and the second word is price.
 * It returns the first word (day)
 */
string extractDay(string line)
{
    int positionOfSpace = line.find(" ");
                       // extract substring from a string
                       // we will talk about this later
    string firstWord = line.substr(0, positionOfSpace);
    return firstWord;
}

/*
 * This function takes a string as a parameter with two words
 * The second word is price. It converts the price as string to
 * price as double and returns the price
 */
double extractPrice(string line)
{
    int positionOfSpace = line.find(" ");
    int sizeOfLine = line.length();
                           // extract substring from a string
                           // we will talk about this later
    string priceAsString = line.substr(positionOfSpace+1, sizeOfLine);
    double price;
    istringstream(priceAsString) >> price; // convert string to double
    return price;
}

/*
 * This function displays array (double-price) elements on a separate line
 */
void displayArray(double arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout  << "$" << arr[i] << endl;
    }
}

/*
 * This function displays array (string-days) elements on a separate line
 */
void displayArray(string arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << endl;
    }
}

// totalBudget function reads the prices array and calculates a sum total
double totalBudget(double prices[])
{
    double sum;
    int index;

    // for loop runs through the prices[] array and totals the prices
    for (index = 0; index <= SIZE; index++)
    {
        sum += prices[index];
    }

    // return sum to main
    return sum;
}

// textFileFunction accepts sumTotal as an argument and writes text into the total.txt file.
void textFileFunction(double sumTotal)
{
    // Declaring output file stream
    ofstream outputFile;

    outputFile.open("total.txt", ios::out);

    // Display error message if outputFile does not open
    if (!outputFile.is_open())
    {
        cout << "The file could not be opened.";
        exit(1);
    }

    // Write the sum total to the text file
    outputFile << "The sum total of Mr. K's budget is $" << sumTotal << ".\n";

    // close the outputFile
    outputFile.close();
}
