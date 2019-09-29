#include "SerialReader.h"

sr::SerialReader::SerialReader(char *path){
    fd = open(path,O_RDWR);
    memset(buf,'0',BUFLENGTH);

    if(fd < 0){
        printf("Error %i from open: %s\n",errno,strerror(errno));
        return;
    }
}
int sr::SerialReader::Init(){
    memset(&tty,0,sizeof tty);

    if(tcgetattr(fd,&tty) != 0){
        printf("Error %i from tcgetattr: %s\n",errno,strerror(errno)); 
        return -1;       
    }

    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CREAD | CLOCAL;

    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO;
    tty.c_lflag &= ~ECHOE;
    tty.c_lflag &= ~ECHONL;
    tty.c_lflag &= ~ISIG;

    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|ICRNL);
    
    tty.c_oflag &= ~OPOST;
    tty.c_oflag &= ~ONLCR;
    
    tty.c_cc[VTIME] = 0;
    tty.c_cc[VMIN] = 5;

    cfsetispeed(&tty,B9600);
    cfsetospeed(&tty,B9600);

    if(tcsetattr(fd,TCSANOW,&tty) != 0){
        printf("Error %i from tcsetattr : %s",errno,strerror(errno));
        return -1;
    }
    return 0;
}

sr::SerialReader::~SerialReader(){
    close(fd);
}

size_t sr::SerialReader::readData(){
    ioctl(fd,TCFLSH,2);
    usleep(200);
    int f = read(fd,buf,BUFLENGTH);
    if(f == -1){
        std::cout << "Failed to read";
        return -1;
    }
    return f;
}

size_t sr::SerialReader::writeData(char *data,int length){
    int f = write(fd,data,length);
    if(f == -1){
        std::cout << "Failed to write";
        return -1;
    }
    return f;
}

void sr::SerialReader::printBuf(){   
    for (int i = 0; i < BUFLENGTH; ++i){
        std::cout << buf[i];
    }
}