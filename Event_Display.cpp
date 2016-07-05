#include <iostream>
#include <string>
#include "Calendar.h"

using namespace std;

bool isInteger(const std::string & s) {
  char* p ;
  strtol(s.c_str(), &p, 10) ;
  return (*p == 0) ;
}

Calendar createCalendar() {
  // read in data from storage/database, harded coded here for simple demo
  Event e1 = {"Birthday party", 120, 2016, 2, 14, false};
  Event e2 = {"Technical discussion", 23, 2016, 11, 24, false};
  Event e3 = {"Press release", 64, 2015, 12, 17, true};
  Event e4 = {"New year party", 55, 2016, 1, 1, false};

  Event e5 = {"Birthday party", 32, 2016, 1, 15, false};
  Event e6 = {"Technical discussion", 5, 2016, 10, 5, false};
  Event e7 = {"Press release", 500, 2016, 7, 4, false};
  Event e8 = {"New year party", 200, 2017, 1, 1, false};
    
  Calendar calendar; 
  calendar.addEvent(e1);
  calendar.addEvent(e2);
  calendar.addEvent(e3);
  calendar.addEvent(e4);
  calendar.addEvent(e5);
  calendar.addEvent(e6);
  calendar.addEvent(e7);
  calendar.addEvent(e8);  
  
  // Sort in advance to same time on queries. For next step, could add user
  // ability to input/delete events.  Data structure / sort would need to switch
  // to binary search tree for faster lookup and deletion.
  calendar.sortByOccasion();
  calendar.sortByInvitedCount();
  calendar.sortByDate();
  return calendar;
}

void event_display_tests () {

  bool result = true; 
  Calendar c = createCalendar();

  // Test if calendar has correct number of events, 
  // and that all show member variables are initialized to true.
  if (c.numEvents() != 8 || !c.show_occasion || !c.show_invited_count ||
     !c.show_day || !c.show_month || !c.show_year)
       result = false;

  // Visual output display tests, must check by visually inspecting console.
  // Turn off test when in production.

  // Test when user selects display by occasion
  c.printByOccasion();
  
  // Test all options when user selects display by invited count
  c.printByInvitedCount(SMALL);   // should display e6, e2, e5
  c.printByInvitedCount(MEDIUM);  // should display e4, e3
  c.printByInvitedCount(LARGE);   // should display e1, e8, e7
  c.printByInvitedCount(ALL);     // should display e6, e2, e5, e4, e3, e1, e8, e7
  
  // Test all non-all inputs when user selects display by date
  c.printByDate(  -1, -1, -1);    // should display e3, e4, e5, e1, e7, e6, e2, e8
  c.printByDate(2016, -1, -1);    // should display e4, e5, e1, e7, e6, e2
  c.printByDate(2016,  1, -1);    // should display e4, e5
  c.printByDate(2016,  1,  1);    // should display e4

  // User input functions: 
  //  - request_user_input
  //  - request_user_input_type
  //  - request_user_input_invited_count
  //  - request_user_input_date
  // tested manually with the same test cases given above for the
  // visual output display tests.

  if (!result) cout << "Test failed\n";
}

int request_user_input_type () {
  string input_type = "";
  int type = -1;
  cout << "Enter the number of the event type to display: " << endl << endl;
  cout << " (1) Occasion" << endl;
  cout << " (2) Invited Count" << endl;
  cout << " (3) Date" << endl << endl;

  do {
    cout << "Type: ";
    getline(cin,input_type);
    if (!input_type.empty() && isInteger(input_type)) 
      type = stoi(input_type);
  } while (type != 1 && type != 2 && type != 3);

  cout << endl;
  return type;
}

int request_user_input_invited_count() {

  string input_count = "";
  int count = -1;

  cout << "Enter the number of the event size to display\n";
  cout << "or just hit enter to display events of all sizes: " << endl << endl;

  cout << " (1) 0 - 50" << endl;
  cout << " (2) 51 - 100" << endl;
  cout << " (3) 101+" << endl << endl;

  do {
    cout << "Size: ";
    getline(cin,input_count);
    if (input_count.empty()) count = 4;
    if (!input_count.empty() && isInteger(input_count)) 
      count = stoi(input_count);
  } while (count != 1 && count != 2 && count != 3 && count != 4);

  cout << endl;
  return count;

}

void request_user_input_date(int &year, int &month, int &day) {

  string input = "";
  year = -2;
  month = -2; 
  day = -2;

  // Ask user for year to display
  cout << "Enter the event year to display\n";
  cout << "or just hit enter to display events for all years: " << endl << endl;

  do {
    cout << "Year: ";
    getline(cin,input);
    if (input.empty()) year = -1;
    if (!input.empty() && isInteger(input)) 
      year = stoi(input);
  } while (year == -2 );
  
  cout << endl;
  if (year == -1) {
    month = -1;
    day = -1;
    return;
  }

  // Ask user for month to display
  cout << "Enter the event month (1-12) to display\n";
  cout << "or just hit enter to display events for all months: " << endl << endl;

  do {
    cout << "Month: ";
    getline(cin,input);
    if (input.empty()) month = -1;
    if (!input.empty() && isInteger(input)) 
      month = stoi(input);
  } while (month == -2 || (month < 1 && month != -1) || month > 12 );

  cout << endl;
  if (month == -1) {
    day = -1;
    return;
  }

  // Ask user for day to display
  cout << "Enter the event day to display\n";
  cout << "or just hit enter to display events for all days: " << endl << endl;

  do {
    cout << "Day: ";
    getline(cin,input);
    if (input.empty()) day = -1;
    if (!input.empty() && isInteger(input)) 
      day = stoi(input);
  } while (day == -2 || (day < 1 && day != -1) || 
           (month == 2 && day > 28 ) || 
           ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) ||
           ((month != 2 && month != 4 && month != 6 && month != 9 && month != 11) &&
            (day > 31)));

  cout << endl;

}

void request_user_input() {
  // With data storage and user auth, can pull specific calendar for user here.
  // For demo, use simple demo data.
  int type;
  int invited_count;
  int year, month, day;
  Calendar calendar = createCalendar();

  cout << "Welcome to your events Calendar! ";
  cout << "You have " << calendar.numEvents() << " event";
  if (calendar.numEvents() != 1) cout << "s";
  cout << "." << endl;

  // request user input on which type of event they'd like to see
  type = request_user_input_type();

  switch (type) {
    case 1:
      calendar.printByOccasion();
      break;
    case 2:
      invited_count = request_user_input_invited_count();
      calendar.printByInvitedCount(invited_count);
      break;
    case 3:
      request_user_input_date(year, month, day);
      calendar.printByDate(year, month, day);
      break;
    default:
      break;
  }
}

int main() {
  
  // Code tests, turn off in production since part of test outputs to console
  // event_display_tests();

  // Request user input
  request_user_input();

  return 0;
}