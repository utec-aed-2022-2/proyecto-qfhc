#include <iostream>
#include <chrono>
#include <iomanip>
#include <string>
#include <functional>
using namespace std;
using namespace std::chrono;
/*
string fecha(){
  time_t f = time(nullptr);
  string fe;
  char dat[40];
  strftime(dat, 30, "%c %Z", localtime(&f));
  fe=dat;
  return fe;
}*/

long long unsigned int fecha(){
  long long unsigned int timestamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
  return timestamp;
}

string unixTimeToHumanReadable(long long unsigned int milliseconds)
{
    long long unsigned int seconds = milliseconds/1000;
    // Save the time in Human
    // readable format
    string ans = "";
 
    // Number of days in month
    // in normal year
    int daysOfMonth[] = { 31, 28, 31, 30, 31, 30,
                          31, 31, 30, 31, 30, 31 };
 
    long int currYear, daysTillNow, extraTime, extraDays,
        index, date, month, hours, minutes, secondss,
        flag = 0;
 
    // Calculate total days unix time T
    daysTillNow = seconds / (24 * 60 * 60);
    extraTime = seconds % (24 * 60 * 60);
    currYear = 1970;
 
    // Calculating current year
    while (true) {
        if (currYear % 400 == 0
            || (currYear % 4 == 0 && currYear % 100 != 0)) {
            if (daysTillNow < 366) {
                break;
            }
            daysTillNow -= 366;
        }
        else {
            if (daysTillNow < 365) {
                break;
            }
            daysTillNow -= 365;
        }
        currYear += 1;
    }
    // Updating extradays because it
    // will give days till previous day
    // and we have include current day
    extraDays = daysTillNow + 1;
 
    if (currYear % 400 == 0
        || (currYear % 4 == 0 && currYear % 100 != 0))
        flag = 1;
 
    // Calculating MONTH and DATE
    month = 0, index = 0;
    if (flag == 1) {
        while (true) {
 
            if (index == 1) {
                if (extraDays - 29 < 0)
                    break;
                month += 1;
                extraDays -= 29;
            }
            else {
                if (extraDays - daysOfMonth[index] < 0) {
                    break;
                }
                month += 1;
                extraDays -= daysOfMonth[index];
            }
            index += 1;
        }
    }
    else {
        while (true) {
 
            if (extraDays - daysOfMonth[index] < 0) {
                break;
            }
            month += 1;
            extraDays -= daysOfMonth[index];
            index += 1;
        }
    }
 
    // Current Month
    if (extraDays > 0) {
        month += 1;
        date = extraDays;
    }
    else {
        if (month == 2 && flag == 1)
            date = 29;
        else {
            date = daysOfMonth[month - 1];
        }
    }
 
    // Calculating HH:MM:YYYY
    hours = extraTime / 3600;
    minutes = (extraTime % 3600) / 60;
    secondss = (extraTime % 3600) % 60;
 
    ans += to_string(date);
    ans += "/";
    ans += to_string(month);
    ans += "/";
    ans += to_string(currYear);
    ans += " ";
    ans += to_string(hours);
    ans += ":";
    ans += to_string(minutes);
    ans += ":";
    ans += to_string(secondss);
 
    // Return the time
    return ans;
}

struct TBData{
    double monto=0;
    string emisor;
    string receptor;
    long long unsigned int fecha;

    TBData(){}

    TBData(double amt, string sender, string reciever, long long unsigned int time){
        monto = amt;
        emisor = sender;
        receptor = reciever;
        fecha = time;
    }

    void print(){
        cout<<endl<<"Transaction"<<endl;
        cout <<"==================================="<<endl;
        cout<<"monto: " << monto <<endl;
        cout<<"emisor: "<< emisor <<endl;
        cout<<"receptor: " << receptor <<endl;
        cout<<"fecha: " << unixTimeToHumanReadable(fecha) <<endl;
    }
};

auto TBData_compare = [](TBData* a, TBData* b) {
    return a->monto > b->monto;
};
auto TBData_compare_f = [](TBData* a, TBData* b) {
    return a->fecha > b->fecha;
};
auto TBData_print = [](TBData* a) {
    a->print();
    return true;
};
