#include "SerialReader.h"

#define PATH "/dev/ttyACM0"

int main(){
    sr::SerialReader sr(PATH);
    if(sr.Init() == 0){              
        std::cout << sr.writeData("H87;",5);                                           
          
    }
    else{
        printf("Something went wrong.");
    }   
}