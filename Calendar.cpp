#include "Calendar.h"

using namespace std;

class CompareOccasion {
public: 
  const bool operator()(const Event &lhs, const Event &rhs) const {
    return lhs.occasion < rhs.occasion;
  }
};

class CompareInvitedCount {
public: 
  const bool operator()(const Event &lhs, const Event &rhs) const {
    return lhs.invited_count < rhs.invited_count;
  }
};

class CompareDate {
public: 
  const bool operator()(const Event &lhs, const Event &rhs) const {
    if (lhs.year != rhs.year) {
      return lhs.year < rhs.year;
    } else if (lhs.month != rhs.month) {
      return lhs.month < rhs.month;
    } else {
      return lhs.day < rhs.day;
    }
  }
};
 
Calendar::Calendar () {
  show_occasion = true;
  show_invited_count = true;
  show_year = true;
  show_month = true;
  show_day = true;
}

void Calendar::addEvent (Event e) {
  events_by_occasion.emplace_back(e);
  events_by_invited_count.emplace_back(e);
  events_by_date.emplace_back(e);
}
  
void Calendar::sortByOccasion () {
  // Case sensitive sort by occasion  
  sort(events_by_occasion.begin(), events_by_occasion.end(), CompareOccasion());
}
  
void Calendar::sortByInvitedCount () {
  sort(events_by_invited_count.begin(), events_by_invited_count.end(), CompareInvitedCount());
}
  
void Calendar::sortByDate () {
  sort(events_by_date.begin(), events_by_date.end(), CompareDate());
}
  
void Calendar::printEvent(Event e) {
  if (show_occasion)                       cout << "Occasion: " << e.occasion << endl;
  if (show_invited_count)                  cout << "Invited Count: " << e.invited_count << endl;
  if (show_month || show_day || show_year) cout << "Date: ";
  if (show_month)                          cout << months[e.month-1] << " ";  
  if (show_day)                            cout << e.day;     
  if (show_day && show_year)               cout << ", ";  
  if (show_year)                           cout << e.year ;
  if (show_month || show_day || show_year) cout << endl;
  
  // Always show if cancelled
  if (e.cancelled) cout << "EVENT CANCELLED\n";
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";  
}
  
void Calendar::printByOccasion () {
    
  // Future improvements could include requesting from user type of occasion
  // and doing regex comparison on types in pre computed types set.  For now
  // print all types.

  if (events_by_occasion.size() == 0) {
    cout << "No events listed" << endl;
    return;
  }

  show_occasion      = false;
  show_invited_count = true;
  show_year          = true;
  show_month         = true;
  show_day           = true;
  
  string current_occasion = "";
  for (int i = 0; i < events_by_occasion.size(); i++) {
    if (events_by_occasion[i].occasion != current_occasion) {
      current_occasion = events_by_occasion[i].occasion;
      cout << "\nOccasion: " << current_occasion << endl;
      cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    }  
    printEvent(events_by_occasion[i]); 
  } 
  cout << endl;
}
  
void Calendar::printByInvitedCount (int size) {

  if (events_by_invited_count.size() == 0) {
    cout << "No events listed" << endl;
    return;
  }

  // For simple demo, loop through all events.  Can improve time by doing binary
  // search on events to find first, and print all events in size range.
  show_occasion      = true;
  show_invited_count = true;
  show_year          = true;
  show_month         = true;
  show_day           = true;
    
  cout << "Event size: ";

  switch(size) {
    case SMALL:
      cout << "0 - 50\n\n";
      break;
    case MEDIUM:
      cout << "51 - 100\n\n";
      break;
    case LARGE:
      cout << "101+\n\n";
      break;
    case ALL:
      cout << "All\n\n";
      break;
    default:
      break;
  }
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    
  for (int i = 0; i < events_by_invited_count.size(); i++) {
    switch (size) {
      case SMALL: 
      if (events_by_invited_count[i].invited_count <= 50) {
        printEvent(events_by_invited_count[i]);   
      }
      break;
      case MEDIUM:
        if (events_by_invited_count[i].invited_count > 50 && 
          events_by_invited_count[i].invited_count <= 100) {
          printEvent(events_by_invited_count[i]);   
      }
      break;
      case LARGE:
        if (events_by_invited_count[i].invited_count > 100) {
        printEvent(events_by_invited_count[i]);   
      }     
      break;
      case ALL:
        printEvent(events_by_invited_count[i]);
      break;
        default:
        break;
    }
  }
  cout << endl;
}
  
void Calendar::printByDate(const int &year, const int &month, const int &day) {
  
  if (events_by_date.size() == 0) {
    cout << "No events listed" << endl;
    return;
  }

  // For simple demo, loop through all events.  Can improve time by doing binary
  // search on events to find first, and print all events in size range.  
  // -1 on year/month/day means print all
  show_occasion      = true;
  show_invited_count = true;
  show_year          = (year == -1)  ? true : false;
  show_month         = (month == -1) ? true : false;
  show_day           = (day == -1)   ? true : false;

  cout << "Date: "; 
  if (month != -1)                            cout << months[month-1] << " "; 
  if (day != -1)                              cout << day; 
  if (day != -1 && year != -1)                cout << ", ";
  if (year != -1)                             cout << year;    
  if (day == -1 && month == -1 && year == -1) cout << "All";    
  cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  
  // Print all events with dates matching input day/month/year
  for (int i = 0; i < events_by_date.size(); i++) {
    if ((year  == -1 || events_by_date[i].year  == year) &&
        (month == -1 || events_by_date[i].month == month) &&
        (day   == -1 || events_by_date[i].day   == day))
          printEvent(events_by_date[i]);
  } 
  cout << endl;
}
  
int Calendar::numEvents () {
  return events_by_occasion.size();
}