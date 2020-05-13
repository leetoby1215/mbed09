#include "mbed.h"
#include "mbed_rpc.h"
/**
 *  This example program has been updated to use the RPC implementation in the new mbed libraries.
 *  This example demonstrates using RPC over serial
**/
RpcDigitalOut myled1(LED1,"myled1");
RpcDigitalOut myled3(LED3,"myled3");
Serial pc(USBTX, USBRX);
void LEDControl(Arguments *in, Reply *out);
RPCFunction rpcLED(&LEDControl, "LEDControl");
double x, y;

int main() {
    //The mbed RPC classes are now wrapped to create an RPC enabled version - see RpcClasses.h so don't add to base class
    // receive commands, and send back the responses
    char buf[256], outbuf[256];
    while(1) {
        memset(buf, 0, 256);
        for (int i = 0; ; i++) {
            char recv = pc.getc();
            if (recv == '\r') {
                pc.printf("\r\n");
                break;
            }
            buf[i] = pc.putc(recv);
        }
        //Call the static call method on the RPC class
        RPC::call(buf, outbuf);
        pc.printf("%s\r\n", outbuf);
    }
}

// Make sure the method takes in Arguments and Reply objects.
void LEDControl (Arguments *in, Reply *out)   {
    bool success = true;
    // In this scenario, when using RPC delimit the two arguments with a space.
    x = in->getArg<double>();
    y = in->getArg<double>();

    // Have code here to call another RPC function to wake up specific led or close it.
    char buffer_1[200];
    char buffer_2[200];
    char outbuf[256];
    char strings_1[20];
    char strings_2[20];
    int red = x;
    int blue = y;
    int n = sprintf(strings_1, "/myled1/write %d", red);
    strcpy(buffer_1, strings_1);
    RPC::call(buffer_1, outbuf);
    int m = sprintf(strings_2, "/myled3/write %d", blue);
    strcpy(buffer_2, strings_2);
    RPC::call(buffer_2, outbuf);
    if (success) {
        out->putData(buffer_1);
        out->putData(buffer_2);
    } else {
        out->putData("Failed to execute LED control.");
    }
}