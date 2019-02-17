//#include "readFrFile1.hpp"
//Hannah Chua PT UOW 6276325
//g++ -std=c++11 readFrFile1.cpp -o readFrFile.exe
//
// Assuming fileIO.h displayUtilities.h together with all *.cpp are in SAME folder
// g++ -std=c++11 fileIO.cpp displayUtilities.cpp assn3.cpp -o assn3.exe

//#include <boost/algorithm/string.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <set>

using namespace std;

struct point //_size_t
{
    int x;
    int y;
    int value;
    string name;
    char LMHP;
    char LMHC;
    //double averagecloud[size]; flexible size but array is fixed size
    //double averagepressure[size]; //array in structs
};

void displayMenuOptions ();
void readCounterCITY(string filename);
void readCounterCLOUD(string filename);
void readCounterPRESSURE(string filename);
string tokenizeString (string input, string delimiter);
void readFileCity (string filename); //point * dataCI);  //,int counter);
void readFileCloud (string filename);
void readFilePressure (string filename);
void printSquareCity(int rows, int cols, point city[]);
void printSquareCloud(int rows, int cols, point cloud[]);
void printSquarePressure(int rows, int cols, point pressure[]);
void printLMHCloud(int rows, int cols, point cloud[]);
void printLMHPressure(int rows, int cols, point pressure[]);

point* city;
point* cloud;
point* pressure; // point
// 1D array on dynamic memory allocation

//void getX&Y (point& temp, string txtX, string txtY);
//void printValueMap (int x, int y, vector <point> data, int checkIfIndicator);

int counter = 0; //global variable
int counter1 = 0;
int counter2 = 0;
int main ()
{

    //} while (usersChoice != 8);
    
    //data can be placed in a software buffer before it is processed.
    /*string* dynamicNameArrayPtr = nullptr; //initialize point <--> string*
     string* dynamicAddrArrayPtr = nullptr;
     dynamicNameArrayPtr = new string[arraySize];
     //typedef city dynamicNameArrayPtr = new city[14]; //14 lines in citylocation.txt
     streambuf *psbuf, *backup;
     backup = cin.rdbuf();     // back up cin's streambuf
     psbuf = inputFile.rdbuf();        // get file's streambuf
     cin.rdbuf(psbuf);         // assign streambuf to cin
     for (int i =0; i < arraySize; i++)
     {
     getline(cin, dynamicNameArrayPtr[i]);
     cout << endl;
     }
     
     cin.rdbuf(backup);        // restore cin's original streambuf
     inputFile.close();
     displayArrayContents(arraySize, dynamicNameArrayPtr, dynamicAddrArrayPtr);
     safelyDeallocateMemory2 (arraySize, dynamicNameArrayPtr, dynamicAddrArrayPtr);
     cout << endl; */
    
    string inputFilename = "TestCases_Config.txt";
    fstream inputFile (inputFilename.c_str(), fstream::in);
    string aLine;
    vector<string> temp;
    
    while (getline (inputFile, aLine))
    {
        //cout << aLine << endl;
        if (aLine.find("Range") != string::npos) //pos2 //!=nullPtr
        {
            string s = tokenizeString(aLine, "-");
            temp.push_back(s);//nested function sylvester
        }
        else if (aLine.find("TestCases_CityLocation.txt") != string::npos) //if citylocation not found, go to end of string
        {
            readCounterCITY("TestCases_CityLocation.txt");
            readFileCity ("TestCases_CityLocation.txt");
            //printSquareCity(xmax, ymax, city);
        }
        else if (aLine.find("TestCases_CloudCover.txt") != string::npos)
        {
            readCounterCLOUD("TestCases_CloudCover.txt");
            readFileCloud ("TestCases_CloudCover.txt");
            //printSquareCloud(xmax, ymax, cloud);
        }
        else if (aLine.find("TestCases_Pressure.txt") != string::npos) // else if
        {
            readCounterPRESSURE("TestCases_Pressure.txt");
            readFilePressure ("TestCases_Pressure.txt");
            //printSquarePressure(xmax, ymax, pressure);
        }
    }
    cout << endl;
    
    for (int i=0; i< temp.size(); i++)
     {
     cout << temp [i] << endl;
     }
     cout << endl; 

 
    size_t sz = temp.size();
    int xmax, ymax;
    xmax = stoi(temp.at(0), &sz);
    ymax = stoi(temp.at(1), &sz); 

    cout << sz;
    cout << xmax;
    cout << ymax;
   
    
    /*init2DArray (xmax, ymax); //put correct args not "variable"
     populate2DArray (xmax, ymax);
     display2DArray (xmax, ymax);
     safelyDeallocateMemory (xmax, ymax);     //(9, 9); */
    int usersChoice = 0;
    
    do
    {
        cout << "Student ID: 6276325" << endl;
        cout << "Student Name: Hannah Chua Hui Zhen" << endl;
        cout << endl;
        cout << "-------------------------------------" << endl;
        cout << "Welcome to Weather Information Processing System!" << endl;
        cout << endl;
        displayMenuOptions ();
        cin >> usersChoice;
      switch (usersChoice)
      {
        case 1 :
            //on int main() no break READ EVERYTHING FROM CONFIG.TXT
            cout << "All records successfully stored. Going back to main menu..." <<endl;
            break;
        case 2 :
            printSquareCity(ymax, xmax, city);
            break;
        case 3 :
            printSquareCloud(ymax, xmax, cloud); //xmax = 8, ymax=10
            break;
        case 4 :
            printLMHCloud(ymax, xmax, cloud);
            break;
        case 5 :
            printSquarePressure(ymax, xmax, pressure);
            break;
        case 6 :
            printLMHPressure(ymax, xmax, pressure);
            break;
        case 7 :
            //calculateACC();
            //calculateAP();
            //calculateRain();
            //printReport();
            break;
        case 8 : cout << "Have a nice day!"  << endl;
      }
    } while (usersChoice != 8);
    
    //DELETE type arrayName [ x ][ y ];
    delete [] city;
    delete [] cloud;
    delete [] pressure;
    return (0);
}

void displayMenuOptions ()
{
    cout << "1) Read in and process a configuration file" << endl;
    cout << "2) Display city map" << endl;
    cout << "3) Display cloud coverage map (cloudiness index)" << endl;
    cout << "4) Display cloud coverage map (LMH symbols)" << endl;
    cout << "5) Display atmospheric pressure map (pressure index)" << endl;
    cout << "6) Display atmospheric pressure map (LMH symbols)" << endl;
    cout << "7) Show weather forecast summary report" << endl;
    cout << "8) Exit" << endl;
    
    cout << "Please enter your choice (1-7) : ";
}

string tokenizeString (string input, string delimiter)
{
    string token1, token2;
    size_t pos = input.find(delimiter); //0-8
    if(pos != string::npos)
    {
        //token1 = input.substr((pos-1), 1);
        token2 = input.substr((pos+1), 2);
    }
    //result.push_back (input);
    return (token2);
}

void readCounterCITY(string filename)
{
    fstream inputFile (filename.c_str(), fstream::in);
    string aline;
    
    while (getline(inputFile, aline))
    {
        if (aline.find("[") != string::npos)
        {
            counter++; //counter start from number from the file read before
        }
    }
    //return (counter);
}

void readCounterCLOUD(string filename)
{
    fstream inputFile (filename.c_str(), fstream::in);
    string aline;
    while (getline(inputFile, aline))
    {
        if (aline.find("[") != string::npos)
        {
            counter1++; //counter start from number from the file read before
        }
    }
    //return (counter);
}

void readCounterPRESSURE(string filename)
{
    fstream inputFile (filename.c_str(), fstream::in);
    string aline;
    while (getline(inputFile, aline))
    {
        if (aline.find("[") != string::npos)
        {
            counter2++; //counter start from number from the file read before
        }
    }
    //return (counter);
}

void readFileCity(string filename)
{
    readCounterCITY(filename);
    //cout << counter;
    city = new point[counter];
    
    fstream inputFile (filename.c_str(), fstream::in);
    string aline;
    string a, b, c, d;
    int i = 0;
    
    //init2DArrayOfPoint (9, 9, point* city);
    while (getline(inputFile, aline))
    {
        if (aline.find("[") != string::npos)
        {
            a = aline.substr((aline.find("-") +1), 1);//aline.size());
            b = aline.substr((aline.find("[") +1), 1); //find first
            c = aline.substr((aline.find("]") -2), 2);
            d = aline.substr((aline.rfind("-")+1), aline.size());
            city[i].x = stoi(b);
            city[i].value = stoi(a);
            city[i].y = stoi(c);
            city[i].name = d;
            i++;
            
        }
    }
}

void readFileCloud(string filename) //in params: string * dynamicAddrArrayPtr
{
    readCounterCLOUD(filename); //read how many lines in txt
    //cout << counter1 << endl;
    cloud = new point[counter1];
    
    fstream inputFile (filename.c_str(), fstream::in);
    string aline;
    string a, b, c;
    int i = 0;
    char L = 'L';
    char M = 'M';
    char H = 'H';
    
    //init2DArrayOfPoint (9, 9, point* cloud);
    
    while (getline(inputFile, aline))
    {
        if (aline.find("[") != string::npos)
        {
            a = aline.substr((aline.find("-") +1), 2);
            b = aline.substr((aline.find("[") +1), 1); //find first [ aline.substr()
            c = aline.substr((aline.find("]") -2), 2);
            cloud[i].x = stoi(b); //x is b y is c
            cloud[i].value = stoi(a);
            cloud[i].y = stoi(c);
            //nested if, statement below is only executed if condition 1 is fulfilled
            if ((0 <= cloud[i].value) && (cloud[i].value < 35)) //(0 <= i) && ( i<=10) not 0 < i < 100
            {
                cloud[i].LMHC = L;
            }
            else if ((35 <= cloud[i].value) && (cloud[i].value < 65))
            {
                cloud[i].LMHC = M;
            }
            else //((65 <= cloud[i].value) && (cloud[i].value < 100))
            {
                cloud[i].LMHC = H;
            }
            i++;
        }
    }
}

void readFilePressure(string filename)
{
    readCounterPRESSURE(filename);
    pressure = new point[counter2];
    fstream inputFile (filename.c_str(), fstream::in);
    string aline;
    string a, b, c, d;
    int i = 0;
    char L = 'L';
    char M = 'M';
    char H = 'H';
    
    //init2DArrayOfPoint (9, 9, point* pressure);//array2DPointPressure);
    
    while (getline(inputFile, aline))
    {
        if (aline.find("[") != string::npos)
        {
            b = aline.substr((aline.find("[") +1), 1); //find first [
            a = aline.substr((aline.find("-") +1), 2);
            c = aline.substr((aline.find("]") -2), 2);
            pressure[i].x = stoi(b);
            pressure[i].value = stoi(a);
            pressure[i].y = stoi(c);
            if ((0 <= pressure[i].value) && (pressure[i].value < 35)) //(0 <= i) && ( i<=10) not 0 < i < 100
            {
                pressure[i].LMHP = L;
            }
            else if ((35 <= pressure[i].value) && (pressure[i].value < 65))
            {
                pressure[i].LMHP = M;
            }
            else //((65 <= cloud[i].value) && (cloud[i].value < 100))
            {
                pressure[i].LMHP = H;
            }
            i++;
        }
    }
}
        
void printSquareCity(int rows, int cols, point city[])
{
    int i, j, k;
    for (i=rows + 1; i >= -1; i--)
    {
        // Print # for each solid row
        if (i==-1 || i==rows + 1)
            for (j=-1; j<=rows + 1; j++)
                cout << "# " << "\t";
        
        // # for hollow cols
        else
        {
            for (j=-1; j<=cols + 1; j++)//(j=0; j<=cols + 2; j++)
            {
                if (j==-1 || j==cols + 1)    //0 to 8 for y col
                    cout << "# ";
                
                else
                    //cout << " ";
                    //numbers inside grid for loop cloud
                    //cloud[k].x == j .y == i cout<<cloud[k].value
                    for (k = 0; k <= counter; k++)
                    {
                        if ((city[k].x == j) && (city[k].y == i))
                            cout << city[k].value;
                    }
                cout << "\t";
            }
        }
        // Move to the next line/row
        cout << "\n";
    }
}

void printSquareCloud(int rows, int cols, point cloud[])
{
    int i, j, k;
    for (i = rows + 1; i >= -1; i-- )//y coordinate
    {
        // Print # for each solid row
        if (i==-1 || i==rows+1)
            for (j=-1; j<=rows + 1; j++)
                cout << "# " << "\t";
        
        // # for hollow cols
        else
        {
            for (j=-1; j<= cols + 1; j++)
            {
                if (j==-1 || j==cols+1)    //x coordinate rows =10, cols =8
                    cout << "# ";
                
                else
                    //numbers inside grid for loop cloud
                    //cloud[k].x == j .y == i cout<<cloud[k].value
                    //cout << cloud[0].value << endl;
                    for (k = 0; k < counter1; k++) //not k = 0; k <= counter1;
                    {
                        if ((cloud[k].x == j) && (cloud[k].y == i))
                            cout << cloud[k].value;
                    }
                cout << "\t";
            }
        }
        // Move to the next line/row
        cout << "\n";
    }
}

void printSquarePressure(int rows, int cols, point pressure[])
{
    int i, j, k;
    for (i = rows + 1; i >= -1; i-- )//(i= 0; i<=rows + 2; i++)
    {
        // Print # for each solid row
        if (i==-1 || i==rows + 1)
            for (j=-1; j<=rows + 1; j++)
                cout << "# " << "\t";
        
        // # for hollow cols
        else
        {
            for (j=-1; j<=cols + 1; j++)
            {
                if (j==-1 || j==cols + 1)    //0 to 8 for y col
                    cout << "# ";
                
                else
                    //numbers inside grid for loop cloud
                    //cloud[k].x == j .y == i cout<<cloud[k].value
                    //cout << cloud[0].value << endl;
                    for (k = 0; k <= counter2; k++)
                    {
                        if ((pressure[k].x == j) && (pressure[k].y == i))
                            cout << pressure[k].value;
                    }
                cout << "\t";
            }
        }
        // Move to the next line/row
        cout << "\n";
    }
}

void printLMHCloud(int rows, int cols, point cloud[])
{
    int i, j, k;
    for (i = rows + 1; i >= -1; i-- )//(i= 0; i<=rows + 2; i++)
    {
        // Print # for each solid row
        if (i==-1 || i==rows + 1)
            for (j=-1; j<=rows + 1; j++)
                cout << "# " << "\t";
        
        // # for hollow cols
        else
        {
            for (j=-1; j<=cols + 1; j++)
            {
                if (j==-1 || j==cols + 1)    //0 to 8 for y col
                    cout << "# ";
                
                else
                    //numbers inside grid for loop cloud
                    //cloud[k].x == j .y == i cout<<cloud[k].value
                    //cout << cloud[0].value << endl;
                    for (k = 0; k <= counter1; k++)
                    {
                        if ((cloud[k].x == j) && (cloud[k].y == i))
                            cout << cloud[k].LMHC;
                    }
                cout << "\t";
            }
        }
        // Move to the next line/row
        cout << "\n";
    }
}

void printLMHPressure(int rows, int cols, point pressure[])
{
    int i, j, k;
    for (i = rows + 1; i >= -1; i-- )//(i= 0; i<=rows + 2; i++)
    {
        // Print # for each solid row
        if (i==-1 || i==rows + 1)
            for (j=-1; j<=rows + 1; j++)
                cout << "# " << "\t";
        
        // # for hollow cols
        else
        {
            for (j=-1; j<=cols + 1; j++)
            {
                if (j==-1 || j==cols + 1)    //0 to 8 for y col
                    cout << "# ";
                
                else
                    //numbers inside grid for loop cloud
                    //cloud[k].x == j .y == i cout<<cloud[k].value
                    //cout << cloud[0].value << endl;
                    for (k = 0; k <= counter2; k++)
                    {
                        if ((pressure[k].x == j) && (pressure[k].y == i))
                            cout << pressure[k].LMHP;
                    }
                cout << "\t";
            }
        }
        // Move to the next line/row
        cout << "\n";
    }
}



