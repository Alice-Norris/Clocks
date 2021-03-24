#include <stdio.h>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

//Begin function declarations

//handles writing the clock to the terminal. 
void PrintClock(string TwelveHourTime, string TwentyFourHourTime);

//clears the terminal screen, provided in 03/13/2021, 2:47 PM announcement
void ClearScreen(); 

//This prints the user menu, takes user input, and returns it as an integer.
void Menu(int &UserChoice, int &HourMod, int &MinuteMod, int &SecondMod);

//Returns formatted time as a string, takes boolean TwelveHourFormat as an argument.
//If TwelveHourFormat is true, time returned uses the 12-hour clock.
//If false, time returned uses the 24-hour clock
void UpdateTime(tm* Time);

void ModifyTime(tm* TimePointer, int HourMod, int MinuteMod, int SecondMod);

string GetTimeString(int HoursOnClock, tm* TimePointer);

//End function declarations
//begin program
int main() {
    int UserChoice = 0;
    int HourMod = 0;
    int MinuteMod = 0;
    int SecondMod = 0;
    string TwelveHourTime;
    string TwentyFourHourTime;
    tm Time;
    tm* TimePointer = &Time;
    do {
        //PrintClock(TwelveHourTime, TwentyFourHourTime);

        UpdateTime(TimePointer);
        ModifyTime(TimePointer, HourMod, MinuteMod, SecondMod);
        TwelveHourTime = GetTimeString(12, TimePointer);
        TwentyFourHourTime = GetTimeString(24, TimePointer);
        PrintClock(TwelveHourTime, TwentyFourHourTime);
        Menu(UserChoice, HourMod, MinuteMod, SecondMod);      
    } 
   while (UserChoice != 4);
}

void Menu(int &UserChoice, int &HourMod, int &MinuteMod, int &SecondMod) {
    string MenuTopAndBottoom = "*************************";
    cout << "\n" << MenuTopAndBottoom << endl;
    cout << "* 1 - Add One Hour\t*" << endl;
    cout << "* 2 - Add One Minute\t*" << endl;
    cout << "* 3 - Add One Second\t*" << endl;
    cout << "* 4 - Exit Program\t*" << endl;
    cout << MenuTopAndBottoom << endl;
    cin >> UserChoice;

    switch (UserChoice) {
    case 1:
        if (HourMod < 23) {
            HourMod += 1;
        }
        else {
            HourMod = 0;
        }
        ClearScreen();
        break;

    case 2:
        if (MinuteMod < 60) {
            MinuteMod += 1;
        }
        else {
            MinuteMod = 0;
        }
        ClearScreen();
        break;

    case 3:
        if (SecondMod < 60) {
            SecondMod += 1;
        }
        else {
            SecondMod = 0;
        }
        ClearScreen();
        break;

    default:
        ClearScreen();
        cout << "Invalid Choice! Please choose from the menu." << endl;
        break;
    }
}


void PrintClock(string TwelveHourTime, string TwentyFourHourTime) {
    string ClockTopAndBottom = "**************************\t**************************";

    cout << ClockTopAndBottom << endl;
    cout << "*     12-Hour Clock      *\t*     24-Hour Clock      *" << endl;
    cout << "*" << TwelveHourTime << "*\t*" << TwentyFourHourTime << "*" << endl;
    cout << ClockTopAndBottom << endl;
}

void ClearScreen() {
    for (int i = 0; i < 40; ++i) {
        cout << endl;
    }
}

void UpdateTime(tm* Time) {
    time_t currentTime = time(NULL);
    localtime_s(Time, &currentTime);
}

void ModifyTime(tm* TimePointer, int HourMod, int MinuteMod, int SecondMod) {
    TimePointer->tm_hour = ((TimePointer->tm_hour + HourMod) % 24);
    TimePointer->tm_min = ((TimePointer->tm_min + MinuteMod) % 60);
    TimePointer->tm_sec = ((TimePointer->tm_sec + SecondMod) % 60);
}

string GetTimeString(int HoursOnClock, tm* TimePointer){
    char TimeChars[26];
    if (HoursOnClock == 12) { //if user indicates a 12-hour-clock is needed
        strftime(TimeChars, sizeof TimeChars, "      %I:%M:%S %p       ", TimePointer);
        
    }
    else if (HoursOnClock == 24) {

        strftime(TimeChars, sizeof TimeChars, "        %H:%M:%S        ", TimePointer);
    }
    else {
        cout << "Something went wrong!";
    }
    string TimeString = TimeChars;
    return TimeString;
}