//
//  main.cpp
//  Projet 01
//
//  Created by Hicham Lakhal on 2022-04-14.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <memory>


using namespace std;

struct first {
    double x,y;
};

int main() {
    int *var1;
    int *var2;
    
    var1= new int;
    var2 = new int;
    *var1 = 10;
    *var2 = 20;
    cout << *var1 << setw(3) << *var2 << endl;
    *var1 = *var2;
    cout << *var1 << setw(3) << *var2 << endl;
    *var1 = 30;
    cout << *var1 << setw(3) << *var2 << endl;
    *var2 = 40;
    cout << *var1 << setw(3) << *var2 << endl;
    return 0;
}

