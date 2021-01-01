#include "serial.h" //Including the library for seial communication
int main(){
    Serial s1("/dev/ttyACM0",115200); //Creating an serial object
    s1.send("Hello");                 //Sending data to the serial port 
    string data = s1.recv();          //Storing the data recieved from port
    cout<<"Recv : "<<data<<endl;      //Printing
    s1.finish();                      //Closing the port
    return 0;
}
