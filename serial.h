#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

using namespace std;

class Serial{
    private:
        int serial;

        void init(long baud){
            struct termios tty;
                
            if(tcgetattr(serial,&tty)!=0){
                printf("[x]Error from tcgetattr : %s \n",strerror(errno));
            }

            struct termios{
                tcflag_t c_iflag;
                tcflag_t c_oflag;
                tcflag_t c_cflag;
                tcflag_t c_lflag;
                cc_t c_line;
                cc_t c_cc[NCCS];
            };

            tty.c_cflag &= ~PARENB;
            tty.c_cflag &= ~CSTOPB;
            tty.c_cflag &= ~CSIZE;
            tty.c_cflag |= CS8;
            tty.c_cflag &= ~CRTSCTS;
            tty.c_cflag |= CREAD | CLOCAL;

            tty.c_lflag &= ~ICANON;
            tty.c_lflag &= ~ECHO;
            tty.c_lflag &= ~ISIG;

            tty.c_iflag &= ~(IXON | IXOFF | IXANY);
            tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);

            tty.c_oflag &= ~OPOST;
            tty.c_oflag &= ~ONLCR;

            tty.c_cc[VTIME] = 10;
            tty.c_cc[VMIN] = 0;

            cfsetispeed(&tty,baud);
            cfsetospeed(&tty,baud);

            if(tcsetattr(serial,TCSANOW, &tty) != 0){
                printf("[x]Error from tcsetattr : %s\n",strerror(errno));
            }
        }

    public:
        Serial(string port,long baud=9600){
            char portar[port.length() + 1];
            strcpy(portar,port.c_str());
            serial = open(portar,O_RDWR);
            if(serial<0){
                cout<<"Error from opening : "<<strerror(errno)<<endl;
            }
            else{
                init(baud);
            }
        }

        void send(string data){
            char str[data.length()+1];
            strcpy(str,data.c_str());
            write(serial,str,sizeof(str));
        }

        string recv(){
            char buff[256];
            string str = "";
            int number = read(serial,&buff,256);
            if(number<0){
                printf("Error in reading : %s\n",strerror(errno));
            }
            str = buff;
            return str;
        }

        void finish(){
            close(serial);
        }
    
};
