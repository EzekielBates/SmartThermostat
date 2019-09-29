#include "SerialReader.h"

#define PATH "/dev/ttyACM0"

int main(){
    sr::SerialReader sr(PATH);
    if(sr.Init() == 0){
        do{      
            if(sr.readData() == 0);    
                sr.printBuf();                            
        }while(true);   
        sr.~SerialReader();           
    }
    else{
        printf("Something went wrong.");
    }   
}