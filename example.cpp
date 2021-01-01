#include "serial.h"
int main(){
    Serial s1("/dev/ttyACM0",115200);
    s1.send("Hello");
    cout<<"Recv : "<<s1.recv()<<endl;
    s1.finish();
    return 0;
}
