#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

const double PI = 3.141592653589793238463;

struct Customer {
  double latitude;
  int user_id;
  string name;
  double longitude;
  double distance;
};

/* Customer comparison used for sort */
class Compare {
public:
  const bool operator()(const Customer &lhs, 
                        const Customer &rhs) const {
    return lhs.user_id < rhs.user_id;
  }
};

bool validLatitude(const string &lat) {
  return stod(lat) <= 90 && stod(lat) >= 0;
}

bool validLongitude(const string &lon) {
  return stod(lon) <= 180 && stod(lon) >= -180;
}

bool validUserID(const string &user_id) {
  return stoi(user_id) >= 0;
}


// Validate that latitude, user_id, name, and longitude exist for each customer 
// input. Additionally validate that latitude is between -90 and 90 degrees, 
// longitude is between -180 and 180 degrees, and user_id is greater than -1.

bool validateCustomerInput(const string &customer, Customer &parsed_customer) {
  stringstream ss (customer);
  string temp;  

  // Get latitude 
  getline(ss, temp, '"');
  getline(ss, temp, '"');
  getline(ss, temp, '"');
  if (!ss.eof()) {
    getline(ss, temp, '"');
    if (temp.size() && validLatitude(temp)) {
      parsed_customer.latitude = stod(temp);
    } else {
      return false;
    }
  } else {
    return false;
  }

  // Get user id
  getline(ss, temp, '"');
  getline(ss, temp, '"');
  getline(ss, temp, ':');
  getline(ss, temp, ' ');
  if (!ss.eof()) {
    getline(ss, temp, ',');
    if (temp.size() && validUserID(temp)) {
      parsed_customer.user_id = stoi(temp);
    } else {
      return false;
	}
  } else {
    return false;
  }

  // Get name 
  getline(ss, temp, '"');
  getline(ss, temp, '"');
  getline(ss, temp, '"');
  if (!ss.eof()) {
    getline(ss, temp, '"');
    if (temp.size()) {
      parsed_customer.name = temp;
    } else {
      return false;
    }
  } else {
    return false;
  }

  // Get longitude
  getline(ss, temp, '"');
  getline(ss, temp, '"');
  getline(ss, temp, '"');
  if (!ss.eof()) {
    getline(ss, temp, '"');
    if (temp.size() && validLongitude(temp)) {
      parsed_customer.longitude = stod(temp);
    } else {
      return false;
    }
  } else {
    return false;
  }
  
  return true;
}

bool checkCustomerDistance(Customer &parsed_customer) {

  double dublin_lat   = 53.3381985 * PI / 180,   // converted to radians 
         dublin_lon   = -6.2592576 * PI / 180,   // converted to radians
         earth_radius = 6371.0,                  // in km
         central_angle;

  central_angle = acos(sin(dublin_lat) * sin(parsed_customer.latitude * PI / 180) +
                       cos(dublin_lat) * cos(parsed_customer.latitude * PI / 180) *
                       cos(abs(dublin_lon - parsed_customer.longitude * PI / 180)));

  parsed_customer.distance = earth_radius * central_angle;
  return parsed_customer.distance <= 100;
}

// Read customers line by line from file. If valid input format
// and customer is within specified distance, add to return vector.
vector<Customer> readCustomersFromFile(const string &input_file) {
  ifstream fid;
  string next_customer; 
  vector<Customer> matches;
  Customer parsed_customer;

  fid.open(input_file);

  while (getline(fid, next_customer)) {
    if (validateCustomerInput(next_customer, parsed_customer)) {
      if (checkCustomerDistance(parsed_customer)) {
        matches.emplace_back(parsed_customer);
      }
    }
  }

  return matches;
}

/* Test is distance calculation is correct */
bool distance_test() {
  Customer close, far;
  close.latitude  =  54.0;
  close.longitude =  -7.0;
  far.latitude    = 130.0;
  far.longitude   =  80.0;

  return checkCustomerDistance(close) &&
         !checkCustomerDistance(far);

}

/* Test if total input path is correct, using input file
   with all error cases. */
bool input_file_test() {
  vector<Customer> customer_matches;
  customer_matches = readCustomersFromFile("customers_short.txt");

  return customer_matches.size() == 1;
}



int main () {
 
  vector<Customer> customer_matches;
  string input_file = "customers.txt";

  // Tests should all return 1 to pass
  if (!input_file_test() && distance_test()) {
    cout << "Tests Failed, Script Aborted" << endl;
  } else {

    /* Read, validate, and check distance on customers */
    customer_matches = readCustomersFromFile(input_file);

    /* Sort matching customers by user id */
    sort(customer_matches.begin(), customer_matches.end(), Compare());

    /* Print all matching customers */
    for (int i = 0; i < customer_matches.size(); i++) {
      printf("Customer: %20s ", customer_matches[i].name.c_str());
      printf("User ID: %6d ", customer_matches[i].user_id);
      printf("Distance(km): %2.0f\n", customer_matches[i].distance);
    }

  }

  return 0;
}