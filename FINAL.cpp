#include <fstream>
#include <iostream>
#include <string>
#define RED     "\033[31m"      // Red 
#define RESET_COLOR "\033[0m"  //RESET_COLOR
#include <string>
#include <limits>
using namespace std;
#include <sstream>
#include <iomanip>
#include <cmath>

//////STRUCT DECLARATION/////
const int NumElements = 118;
const int NumCations = 99;  //change to 99
const int NumAnions = 43; //change to 43
const int NumThermo = 110;

struct ElementData {
    string ElementChmForm;
    int ElementCharge;
    string ElementName;
    double MassOfElement;
    int AtomicNum;
};

struct CationData {
    string CationChmForm;
    int CationCharge;
    string CationName;
    double MassOfCation;
};

struct AnionData {
    string AnionChmForm;
    int AnionCharge;
    string AnionName;
    double MassOfAnion;
};

struct ThermodynamicData {
    string IonChmForm;
    double H;
    double S;
    double G;
};

CationData myCations[NumCations];
AnionData myAnions[NumAnions];
ElementData myElements[NumElements];
ThermodynamicData myThermo[NumThermo];


////////FUNCTIONS////////
int displayMenu() {
    int userInput;
    while (true) {
        cout << "\nMenu:" << endl << endl;
        cout << "1: Print an Element Info" << endl;
        cout << "2: Calculate Molar Mass of Ionic Compound" << endl;
        cout << "3: Calculate a double displacement reaction's " << "\U0001F53A" << " H\u00B0 rxn " << "\U0001F53A" << " S\u00B0 rxn " << "\U0001F53A" << " G\u00B0 rxn " << endl;
        cout << RED << "99: Quit" << RESET_COLOR << endl;
        cout << "Enter your choice: ";

        if (cin >> userInput) {
            if (userInput == 1 || userInput == 2 || userInput == 3 || userInput == 99) {
                break;
            }
            else {
                cout << "Invalid choice. Please enter a valid option." << endl;
            }
        }
        else {
            return userInput;
        }
    }
    return userInput;
}


int FindElementIndex(string& ElementChmForm) {
    for (int i = 0; i < NumElements; i++) {
        if (myElements[i].ElementChmForm == ElementChmForm) {
            return i;
        }
    }
    return -1;
}


int FindCationIndex(const string& cationChmForm) {
    for (int i = 0; i < NumCations; i++) {
        if (myCations[i].CationChmForm == cationChmForm) {
            return i;
        }
    }
    return -1;
}

int FindAnionIndex(const string& anionChmForm) {
    for (int i = 0; i < NumAnions; i++) {
        if (myAnions[i].AnionChmForm == anionChmForm) {
            return i;
        }
    }
    return -1;
}


int FindThermoIndex(const string& ionChmForm) {
    for (int i = 0; i < NumThermo; i++) {
        if (myThermo[i].IonChmForm == ionChmForm) {
            return i;
        }
    }
    return -1;
}

void outputElementData(const ElementData& element) {
    cout << "\n\t______________________" << endl;
    cout << setw(8) << "|" << setw(12) << element.AtomicNum << setw(11) << " |" << endl;
    cout << setw(8) << "|" << setw(23) << "|" << "\n" << setw(8) << "|" << setw(12) << element.ElementChmForm << setw(11) << "|" << endl;
    cout << setw(8) << "|" << setw(23) << "|" << "\n" << setw(8) << "|" << setw(15) << element.ElementName << setw(8) << "|" << endl;
    cout << setw(8) << "|" << setw(23) << "|" << "\n" << setw(8) << "|" << setw(14) << element.MassOfElement << setw(9) << "|" << endl;
    cout << setw(8) << "|" << setw(5) << "______________________" << "|" << endl;
}


void SetCation(const CationData& cation) {
    cout << cation.CationChmForm << " +" << cation.CationCharge << " " << cation.CationName << " " << cation.MassOfCation << endl;
}


void SetAnion(const AnionData& anion) {
    cout << anion.AnionChmForm << " -" << anion.AnionCharge << " " << anion.AnionName << " " << anion.MassOfAnion << endl;
}


void SetThermo(const ThermodynamicData& thermoion) {
    cout << thermoion.IonChmForm << " " << thermoion.H << " " << thermoion.S << " " << thermoion.G << endl;
}



int OpenPTFile() {
    //OPEN FILE PERIODIC TABLE FILE 
    ifstream inFile("Periodic Table.txt");

    if (!inFile) {
        cout << "Error: Unable to open 'Periodic Table.txt'" << endl;
        return 1;
    }
    else {
        cout << "Opened 'Periodic Table.txt' " << endl;
    }


    //READ PERIODIC TABLE FILE
    for (int i = 0; i < NumElements; i++) {
        if (!(inFile >> myElements[i].ElementChmForm >> myElements[i].ElementCharge >> myElements[i].ElementName >> myElements[i].MassOfElement >> myElements[i].AtomicNum)) {
            break;
        }
    }
    inFile.close();
    return 1;
}


int OpenCCFile() {
    //OPEN CATION FILE
    ifstream cationFile("Common Cations.txt");

    if (!cationFile) {
        cout << "Error: Unable to open 'Common Cations.txt'" << endl;
        return 1;
    }
    else {
        cout << "Opened 'Common Cations.txt' " << endl;
    }
    //READ CATION FILE
    for (int i = 0; i < NumCations; i++) {
        if (!(cationFile >> myCations[i].CationChmForm >> myCations[i].CationCharge >> myCations[i].CationName >> myCations[i].MassOfCation)) {
            break;
        }
    }
    cationFile.close();
    return 1;
}


int OpenCAFile() {
    //OPEN ANION FILE 
    ifstream anionFile("Common Anions.txt");

    if (!anionFile) {
        cout << "Error: Unable to open 'Common Anions.txt'" << endl;
        return 1;
    }
    else {
        cout << "Opened 'Common Anions.txt' " << endl;
    }

    //READ ANION FILE
    for (int i = 0; i < NumAnions; i++) {
        string line;
        if (getline(anionFile, line)) {
            stringstream ss(line);
            if (!(ss >> myAnions[i].AnionChmForm >> myAnions[i].AnionCharge >> myAnions[i].AnionName >> myAnions[i].MassOfAnion)) {
                break;
            }
        }
        else {
            break;
        }
    }
    anionFile.close();
    return 1;
}


int CalcMM(string cation, string anion) {
    //CALCULATE MOLAR MASS 
    double ionmass;

    int cationIndex = FindCationIndex(cation);
    int anionIndex = FindAnionIndex(anion);

    if (cationIndex != -1 && anionIndex != -1) {
        if (myAnions[anionIndex].AnionCharge == myCations[cationIndex].CationCharge) {
            ionmass = myAnions[anionIndex].MassOfAnion + myCations[cationIndex].MassOfCation;
            cout << "\nThe MM of " << cation << anion << " the ion is " << ionmass << "\n";
        }
        else {
            ionmass = (myAnions[anionIndex].AnionCharge * myCations[cationIndex].MassOfCation) +
                (myCations[cationIndex].CationCharge * myAnions[anionIndex].MassOfAnion);
            cout << "\nThe MM of the ion: " << cation << myAnions[anionIndex].AnionCharge << "(" << anion << ")" << myCations[cationIndex].CationCharge << " " << ionmass << "\n";
        }
    }
    else {
        cout << "Cation not found." << endl;
    }
    return 1;
}

int OpenTDFile() {
    //OPEN Thermo FILE
    ifstream ThermoFile("Thermo.txt");

    if (!ThermoFile) {
        cout << "Error: Unable to open 'Thermo.txt' " << endl;
        return 1;
    }
    else {
        cout << "Opened 'Thermo.txt' " << endl;
    }
    //READ Thermo FILE
    for (int i = 0; i < NumThermo; i++) {
        if (!(ThermoFile >> myThermo[i].IonChmForm >> myThermo[i].H >> myThermo[i].S >> myThermo[i].G)) {
            break;
        }
    }
    return 1;
}

int main() {


    ///CHOICES
    int choice;

    while (true) {
        //DISPLAY MENU
        choice = displayMenu();

        //CHOICE 1
        if (choice == 1) {

            OpenPTFile();



            //ASK USER FOR CHEMICAL 
            string elementChmForm;
            cout << "Enter element's name (EX: Ca): ";
            cin >> elementChmForm;

            int elementIndex = FindElementIndex(elementChmForm);
            //VALIDATE CHEMICAL
            if (elementIndex != -1) {
                outputElementData(myElements[elementIndex]);
            }
            else {
                cout << "Element not found." << endl;
            }
            //CLOSE FILE

        //CHOICE 2
        } if (choice == 2) {

            string cation;
            string anion;

            OpenCCFile();

            //GET CATION 
            cout << "\nEnter in the Cation of the Ion you wish to find the MM of (EX: in the form Ca): ";
            //VALIDATE CATION
            do {
                cin >> cation;

                int cationIndex = FindCationIndex(cation);

                if (cationIndex != -1) {
                    SetCation(myCations[cationIndex]);
                    break;
                }
                else {
                    cout << "Cation not found. Please enter a valid cation: ";
                }
            } while (true);


            OpenCAFile();

            //GET ANION
            cout << "\nEnter in the Anion of the Ion you wish to find the MM of (EX: in the form SO4): ";
            //VALIDATE ANION
            do {
                cin >> anion;

                int anionIndex = FindAnionIndex(anion);

                if (anionIndex != -1) {
                    SetAnion(myAnions[anionIndex]);
                    break;
                }
                else {
                    cout << "Anion not found. Please enter a valid anion: ";
                }
            } while (true);

            CalcMM(cation, anion);

        } if (choice == 3) {

            string FirstChem;
            string SecondChem;
            string ThirdChem;
            string FourthChem;

            OpenTDFile();


            //FIRST CHEMCIAL 
            cout << "\nEnter in the 1st Chemical in the Reaction (EX: in the form CH3OH(l)): ";
            //VALIDATE CATION
            do {
                cin >> FirstChem;

                int ThermoIndex = FindThermoIndex(FirstChem);

                if (ThermoIndex != -1) {
                    SetThermo(myThermo[ThermoIndex]);
                    break;
                }
                else {
                    cout << "Chemical not found. Please enter a valid Chemical: ";
                }
            } while (true);


            int Coefficient1;
            do {

                cout << "What is the Coefficient in front of the first chemical (if there is no coefficient put 1): ";
                cin >> Coefficient1;

                // Validate against negative numbers
                if (Coefficient1 < 0) {
                    cout << "Negative number entered. Please enter a non-negative coefficient." << endl;
                }
                else {
                    cout << "\n " << endl;
                }
            } while (Coefficient1 < 0);

            //SECOND CHEMICAL 

            cout << "\nEnter in the 2nd Chemical in the Reaction (EX: in the form H2(g)): ";

            //VALIDATE CATION
            do {
                cin >> SecondChem;

                int ThermoIndex = FindThermoIndex(SecondChem);

                if (ThermoIndex != -1) {
                    SetThermo(myThermo[ThermoIndex]);
                    break;
                }
                else {
                    cout << "Chemical not found. Please enter a valid Chemical: ";
                }
            } while (true);


            int Coefficient2;
            do {

                cout << "What is the Coefficient in front of the second chemical (if there is no coefficient put 1): ";
                cin >> Coefficient2;

                // Validate against negative numbers
                if (Coefficient2 < 0) {
                    cout << "Negative number entered. Please enter a non-negative coefficient." << endl;
                }
                else {
                    cout << "\n " << endl;
                }
            } while (Coefficient2 < 0);

            //THRID CHEMICAL

            cout << "\nEnter in the 3rd Chemical in the Reaction (EX: in the form C2H6(g)): ";
            //VALIDATE CATION
            do {
                cin >> ThirdChem;

                int ThermoIndex = FindThermoIndex(ThirdChem);

                if (ThermoIndex != -1) {
                    SetThermo(myThermo[ThermoIndex]);
                    break;
                }
                else {
                    cout << "Chemical not found. Please enter a valid Chemical: ";
                }
            } while (true);


            int Coefficient3;
            do {

                cout << "What is the Coefficient in front of the third chemical (if there is no coefficient put 1): ";
                cin >> Coefficient3;

                // Validate against negative numbers
                if (Coefficient3 < 0) {
                    cout << "Negative number entered. Please enter a non-negative coefficient." << endl;
                }
                else {
                    cout << "\n " << endl;
                }
            } while (Coefficient3 < 0);

            //FOURTH CHEMICAL 

            cout << "\nEnter in the 4th Chemical in the Reaction (EX: in the form H2O(l)): ";
            //VALIDATE CATION
            do {
                cin >> FourthChem;

                int ThermoIndex = FindThermoIndex(FourthChem);

                if (ThermoIndex != -1) {
                    SetThermo(myThermo[ThermoIndex]);
                    break;
                }
                else {
                    cout << "Chemical not found. Please enter a valid Chemical: ";
                }
            } while (true);


            int Coefficient4;
            do {

                cout << "What is the Coefficient in front of the fourth chemical (if there is no coefficient put 1): ";
                cin >> Coefficient4;

                // Validate against negative numbers
                if (Coefficient4 < 0) {
                    cout << "Negative number entered. Please enter a non-negative coefficient." << endl;
                }
                else {
                    cout << "\n " << endl;
                }
            } while (Coefficient4 < 0);

            // Find thermo indices for all chemicals
            int firstThermoIndex = FindThermoIndex(FirstChem);
            int secondThermoIndex = FindThermoIndex(SecondChem);
            int thirdThermoIndex = FindThermoIndex(ThirdChem);
            int fourthThermoIndex = FindThermoIndex(FourthChem);

            double HRXN;
            double SRXN;
            double GRXN;

            if (firstThermoIndex != -1 && secondThermoIndex != -1 && thirdThermoIndex != -1 && fourthThermoIndex != -1) {
                // Calculate enthalpy change for the reaction
                HRXN = (Coefficient3 * myThermo[thirdThermoIndex].H + Coefficient4 * myThermo[fourthThermoIndex].H) -
                    (Coefficient1 * myThermo[firstThermoIndex].H + Coefficient2 * myThermo[secondThermoIndex].H);
                SRXN = (Coefficient3 * myThermo[thirdThermoIndex].S + Coefficient4 * myThermo[fourthThermoIndex].S) -
                    (Coefficient1 * myThermo[firstThermoIndex].S + Coefficient2 * myThermo[secondThermoIndex].S);
                GRXN = (Coefficient3 * myThermo[thirdThermoIndex].G + Coefficient4 * myThermo[fourthThermoIndex].G) -
                    (Coefficient1 * myThermo[firstThermoIndex].G + Coefficient2 * myThermo[secondThermoIndex].G);

                cout << "The \U0001F53A H\u00B0 is: " << fixed << setprecision(5) << HRXN << " KJ" << endl;
                cout << "The \U0001F53A S\u00B0 is: " << fixed << setprecision(5) << SRXN << " KJ/K" << endl;
                cout << "The \U0001F53A G\u00B0 is: " << fixed << setprecision(5) << GRXN << " KJ" << endl;

            }
            else {
                cout << "\n" << endl;
            }

            //OPTION 99
        }
        else if (choice == 99) {
            cout << "Exiting the program." << endl;
            break;
        }
        else {
            //cout << "Invalid choice. Please try again." << endl;
        }
    }




    return 0;
}