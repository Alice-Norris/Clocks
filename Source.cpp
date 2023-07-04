// Copyright 2023 Alice Norris. Subject to MIT License.

#include <stdio.h>
#include <iostream>
#include <string>
#include <ctime>

// Handles writing the clock to the terminal.
void PrintClock(std::string reg_time, std::string mil_time);

// Clears the terminal screen, provided by instructor in course.
void ClearScreen();

// Prints user menu, handles user input.
void Menu(int choice, int* hour_mod, int* min_mod, int* sec_mod);

// Gets current system time.
void UpdateTime(tm* time_ptr);

// Modifies current time of passed tm pointer using modifier values.
void ModifyTime(tm* time_ptr, int hour_mod, int min_mod, int sec_mod);

// Converts a tm struct into a time string using strftime, 12/24 hour clock
// specified by mil_time bool (true for 24, false for 12).
void GetTimeString(bool mil_time, std::string* time_str, tm* time_ptr);

int main() {
    int choice = 0;
    // Modifier, used to apply user set modifications to the time.
    int hour_mod = 0;
    int min_mod = 0;
    int sec_mod = 0;
    // Both strings are used at once in PrintClock to print 12h and 24h clocks.
    std::string reg_time;
    std::string mil_time;
    // tm struct, to hold the actual time data.
    tm time;
    do {
        UpdateTime(&time);
        ModifyTime(&time, hour_mod, min_mod, sec_mod);
        GetTimeString(false, &reg_time, &time);
        GetTimeString(true, &mil_time, &time);
        PrintClock(reg_time, mil_time);
        Menu(choice, &hour_mod, &min_mod, &sec_mod);
    } while (choice != 4);
}

void Menu(int choice, int* hour_mod, int* min_mod, int* sec_mod) {
    std::string menu_border = "*************************";
    std::cout << "\n" << menu_border << std::endl
              << "* 1 - Add One Hour\t*" << std::endl
              << "* 2 - Add One Minute\t*" << std::endl
              << "* 3 - Add One Second\t*" << std::endl
              << "* 4 - Exit Program\t*" << std::endl
              << menu_border << std::endl;

    std::cin >> choice;

    switch (choice) {
    case 1:
        if (*hour_mod < 23) {
            *hour_mod += 1;
        } else {
            hour_mod = 0;
        }
        break;
    case 2:
        if (*min_mod < 60) {
            *min_mod += 1;
        } else {
            *min_mod = 0;
        }
        break;
    case 3:
        if (*sec_mod < 60) {
            *sec_mod += 1;
        } else {
            *sec_mod = 0;
        }
        break;
    case 4:
      exit(0);
    default:
        std::cout << "Invalid Choice! Please choose from menu." << std::endl;
        break;
    }

    ClearScreen();
}


void PrintClock(std::string reg_time, std::string mil_time) {
    std::string border = "*************************\t*************************";
    std::cout << border << std::endl
        << "*     12-Hour Clock     *\t*     24-Hour Clock     *" << std::endl
        << "*      " << reg_time << "*\t*      " << mil_time
        << "*" << std::endl<< border << std::endl;
}

void ClearScreen() {
    for (int i = 0; i < 40; ++i) {
        std::cout << std::endl;
    }
}

void UpdateTime(tm* time_ptr) {
    time_t curr_time = time(NULL);
    localtime_s(time_ptr, &curr_time);
}

void ModifyTime(tm* time_ptr, int hour_mod, int min_mod, int sec_mod) {
    time_ptr->tm_hour = ((time_ptr->tm_hour + hour_mod) % 24);
    time_ptr->tm_min = ((time_ptr->tm_min + min_mod) % 60);
    time_ptr->tm_sec = ((time_ptr->tm_sec + sec_mod) % 60);
}

void GetTimeString(bool mil_time, std::string* time_str, tm* time_ptr) {
    // Time should be no longer than 26 characters using these format strings.
    char time_chars[26];
    if (!mil_time) {
        strftime(time_chars, sizeof time_chars, "\t%I:%M:%S %p\t", time_ptr);
    } else {
        strftime(time_chars, sizeof time_chars, "\t%H:%M:%S\t", time_ptr);
    }
    *time_str = std::string(time_chars);
}
