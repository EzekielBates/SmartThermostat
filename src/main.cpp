#include "SerialReader.h"

#define PATH "/dev/ttyACM0"

int main(){
    sr::SerialReader sr(PATH);
    if(sr.Init() == 0){
        sr.readData();    
        sr.printBuf();
        sr.~SerialReader(); 
    }
    else{
        printf("Something went wront.");
    }
}