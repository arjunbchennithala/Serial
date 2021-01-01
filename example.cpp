#include "serial.h" //Including the library for seial communication
int main(){
    Serial s1("/dev/ttyACM0",115200); //Creating a serial object with its file location and baud rate.Leaving baud rate field will select the default rate=9600
    s1.send("Hello");                 //Sending data to the serial port 
    string data = s1.recv();          //Storing the data recieved from port
    cout<<"Recv : "<<data<<endl;      //Printing
    s1.finish();                      //Closing the port
    return 0;
}
