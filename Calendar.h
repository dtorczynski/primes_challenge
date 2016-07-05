#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Event {
  string occasion;
  int  invited_count;
  int  year;
  int  month;
  int  day;
  bool cancelled;
};

enum EVENT_SIZE {
  SMALL  = 1, 
  MEDIUM = 2,
  LARGE  = 3, 
  ALL    = 4
};

const string months[12] =  {"January", 
                            "February", 
                            "March", 
                            "April", 
                            "May", 
                            "June", 
                            "July", 
                            "August", 
                            "September", 
                            "October", 
                            "November", 
                            "December"};

class Calendar {

public: 
  bool show_occasion;
  bool show_invited_count;
  bool show_year;
  bool show_month; 
  bool show_day;
  
  Calendar ();

  void addEvent (Event e);
  
  void sortByOccasion ();
  
  void sortByInvitedCount ();
  
  void sortByDate ();
  
  void printEvent(Event e);
  
  void printByOccasion ();
  
  void printByInvitedCount (int size);
  
  void printByDate (const int &year, const int &month, const int &day);
  
  int numEvents ();

private: 
  vector<Event> events_by_occasion, 
                events_by_invited_count,
                events_by_date;  
};