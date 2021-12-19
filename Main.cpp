/*
Author: Taylor Wilcox
Due Date: 12/12/2021

Purpose: Build a Grocery Tracking Program for the Corner Grocery store utilizing
a text file which contains a list of items purchased for the day. Display data based on
user selection. Some displays require user input.
*/

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;


/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("Python");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"Python");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;

	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"Python+++");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

void menu() {
	int uChoice, itemQuantity;
	char quit;
	string search, itemName;
	ifstream fileInput;
	
	quit = 'N';

	while (quit == 'N') {
		cout << "MENU" << endl;
		cout << "1: List entire day's purchased items & number of times each item was purchased." << endl;
		cout << "2: Display number of times an item was purchased" << endl; //requires user input
		cout << "3: Display text-based histogram of all items purchased in a give day" << endl;
		cout << "4: Exit Program" << endl;

		cin >> uChoice;
		
		if (uChoice == 1) {
			CallProcedure("listAllItems");
			//menu creation validation: cout << "Option 1 selected" << endl;
		}
		else if (uChoice == 2) {
			cout << "Enter search word or item name" << endl;
			cin >> search;
			cout << search << " : " << callIntFunc("PrintMe", search) << endl;;
			//menu creation: cout << "Option 2 selected" << endl;
		}
		else if (uChoice == 3) {
			CallProcedure("WriteDatFile");
			//menu creation: cout << "Option 3 selected" << endl;
			//testing return to program spot
			//cout << "HELLLOOOO" << endl;

			itemQuantity = 0;

			fileInput.open("frequency.dat");
			//prime first set of info
			fileInput >> itemName;
			fileInput >> itemQuantity;

			while (!fileInput.fail()) {
				cout << itemName;
				for (int i = 0; i < itemQuantity; i++) {
					cout << "*";
				}
				cout << endl;
				//get next set of info
				fileInput >> itemName;
				fileInput >> itemQuantity;
			}
			fileInput.close();
			
		}
		else if (uChoice == 4) {
			quit = 'Y';
			cout << "Program exited." << endl;
		}
		else {
			cout << "Please try again." << endl;
			menu();
		}
	}

}


void main()
{
	menu();
	
	/* starter code
	CallProcedure("printsomething");
	cout << callIntFunc("PrintMe", "House") << endl;
	cout << callIntFunc("SquareValue", 2);
	*/
	
}