#pragma once
#include <sys/types.h>
#include <sys/stat.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

#define BUFLENGTH 20

namespace sr{
    class SerialReader{
        private:
            int fd;
            struct termios tty;
            char buf[BUFLENGTH];
        public:
        SerialReader(char *path);
        int Init();
        size_t readData();  
        size_t writeData(char *data,int length);    
        void printBuf();  
        ~SerialReader();
    };
}