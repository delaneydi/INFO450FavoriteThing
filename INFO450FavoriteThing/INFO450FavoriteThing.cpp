// INFO450FavoriteThing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int READERROR = 100;
const int WRITEERROR = 200;
const int ARRAYSIZE = 100;

class favoriteSneaker
{
	string sneakerName;
	string sneakerBrand;
	string sneakerColor;
	string sneakerType;
	int sneakerSize;
public:
	favoriteSneaker();
	favoriteSneaker(string name, string brand, string color, string type, int size);
	void captureFavoriteSneaker();
	void showFavoriteSneaker();
	int saveFavoriteSneaker(ofstream &outfile);
};

class favoriteSneakerList
{
	favoriteSneaker **list;
	int numSneakers;
	int listsize;
	int ReallocateArray();

public:
	favoriteSneakerList();
	~favoriteSneakerList();
	void GetUserInput();
	void showFavoriteSneakerList();
	int saveFavoriteSneakerList(string filename);
	int readFavoriteSneakerList(string filename);
};

favoriteSneaker::favoriteSneaker()
{
	sneakerName = ""; sneakerBrand = ""; sneakerColor = ""; sneakerType = ""; sneakerSize = 0;
}

favoriteSneaker::favoriteSneaker(string name, string brand, string color, string type, int size)
{
	sneakerName = name;
	sneakerBrand = brand;
	sneakerColor = color;
	sneakerType = type;
	sneakerSize = size;
}

void favoriteSneaker::captureFavoriteSneaker()
{
	cout << "Sneaker Name? -->";
	getline(cin, sneakerName);
	cout << "Sneaker Brand?  -->";
	getline(cin, sneakerBrand);
	cout << "Sneaker Color? -->";
	getline(cin, sneakerColor);
	cout << "Sneaker Type? -->";
	getline(cin, sneakerType);
	cout << "Sneaker Size? -->";
	cin >> sneakerSize;
	cin.ignore();
	cin.clear();
}

void favoriteSneaker::showFavoriteSneaker()
{
	cout << "Sneaker Name : " << sneakerName << " Sneaker Brand : " << sneakerBrand << " Color : " << sneakerColor << "Type : " << sneakerType << "Size : " << sneakerSize << endl;
}

int favoriteSneaker::saveFavoriteSneaker(ofstream& outfile)
{
	if (outfile.is_open())
	{
		outfile << sneakerName << "|" << sneakerBrand << "|" << sneakerColor << "|" << sneakerType << "|" << sneakerSize << endl;
		return 0;
	}
	else
		return WRITEERROR;
}

favoriteSneakerList::favoriteSneakerList()
{
	list = new favoriteSneaker*[ARRAYSIZE];
	numSneakers = 0;
	listsize = ARRAYSIZE;
}

favoriteSneakerList::~favoriteSneakerList()
{
	for (int i = 0; i < numSneakers; i++)
	{
		delete list[i];
	}
	delete[]list;
}

int favoriteSneakerList::ReallocateArray()
{
	favoriteSneaker **temp;
	temp = new favoriteSneaker*[listsize + ARRAYSIZE];
	listsize = listsize + ARRAYSIZE;
	for (int i = 0; i < numSneakers; i++)
	{
		temp[i] = list[i];
	}

	delete[]list;
	list = temp;
	return 0;
}

void favoriteSneakerList::GetUserInput()
{
	string answer = "Y";
	cout << "Enter New Favorite Sneaker? Y/N?" << endl;
	getline(cin, answer);
	while (answer == "Y" || answer == "y")
	{
		list[numSneakers] = new favoriteSneaker();
		list[numSneakers]->captureFavoriteSneaker();
		numSneakers++;
		cout << "Enter New Favorite Sneaker? Y/N?" << endl;
		getline(cin, answer);
	}

}

void favoriteSneakerList::showFavoriteSneakerList()
{
	for (int i = 0; i < numSneakers; i++)
		list[i]->showFavoriteSneaker();
}

int favoriteSneakerList::saveFavoriteSneakerList(string filename)
{
	ofstream output(filename, ios::trunc);
	if (output)
	{
		for (int i = 0; i < numSneakers; i++)
		{
			list[i]->saveFavoriteSneaker(output);
		}
		output.close();
	}
	else
	{
		return WRITEERROR;
	}
	return 0;
}

int favoriteSneakerList::readFavoriteSneakerList(string filename)
{
	string iname, ibrand, icolor, itype, isize;
	ifstream infile(filename, ios::in);
	if (!infile)
	{
		cout << "File could not be opened for reading" << endl;
		return READERROR;
	}

	while (!infile.eof())
	{
		if (numSneakers == listsize)
		{
			ReallocateArray();
		}
		getline(infile, iname, '|');
		if (!iname.empty())
		{
			getline(infile, ibrand, '|');
			getline(infile, icolor, '|');
			getline(infile, itype, '|');
			getline(infile, isize);
			int size = stoi(isize);
			list[numSneakers] = new favoriteSneaker(iname, ibrand, icolor, itype, size);
			numSneakers++;
		}
	}
	infile.close();
	return 0;
}


int main()
{
	string filename = "c:\\users\\desmund\\desktop\\favorite_sneaker_list.txt";
	favoriteSneakerList myFavoriteSneaker;
	string answer;
	int error;
	error = myFavoriteSneaker.readFavoriteSneakerList(filename);
	if (error)
	{
		cout << "Cannot read favorite sneaker list - continue creating new list? Y/N -->";
		getline(cin, answer);
		if (answer != "Y" && answer != "y")
		{
			return 1;
		}
	}
	myFavoriteSneaker.GetUserInput(); 
	myFavoriteSneaker.saveFavoriteSneakerList(filename);
	myFavoriteSneaker.showFavoriteSneakerList();

	return 0;
}



