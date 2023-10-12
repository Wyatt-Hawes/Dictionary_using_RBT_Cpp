#include <csetjmp>
#include <csignal>
#include <cstdbool>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>

#include"Dictionary.h"
#include<iostream>
#include<string>

int main(){

    //std::cout << "hello\n";
    /*
    Dictionary d;
    d.setValue("a", 1);
    d.setValue("b", 2);
    d.setValue("f", 7);
    d.setValue("g", 8);
    d.setValue("h", 9);
    d.setValue("c", 3);
    d.setValue("d", 4);
    d.setValue("e", 5);


    printf("------------------\n");
    std::cout << d.pre_string();
    printf("------------------\n");

    //d.remove("e");
    //d.remove("g");
    d.remove("f");

    printf("size: %d\n", d.size());
    printf("------------------\n");
    std::cout << d;
    printf("------------------\n");
    std::cout << d.pre_string();
    printf("------------------\n");
    */
   Dictionary A;
   Dictionary B;
    std::string s;
    A.setValue("a", 1);
    s =  A.pre_string();

    std::cout << "-------\n" + s;
    A.setValue("b", 5);
    s =  A.pre_string();

    std::cout << "-------\n"+ s + "-------\n";
    A.setValue("c", 16);
    s =  A.pre_string();
    
    std::cout << "-------\n"+ s;

    std::cout << "-------\n"+ s;
    A.setValue("d", 176);
    s =  A.pre_string();

    std::cout << "-------\n"+ s;
    A.setValue("e", 3214);
    s =  A.pre_string();
    std::cout << "-------\n"+ s;



    A.begin();
    A.next();
    A.next();

    if (A.currentKey() != "c" || A.currentVal() != 16){
      std::cout << "failed: " + A.currentKey() + "\n";
    }
      






    return 0;
}