#include "serial.h"
int main(){
    Serial s("/dev/ttyACM0",115200);
    s.send("Hello");
    cout<<"Recv : "<<s.recv()<<endl;
    return 0;
}