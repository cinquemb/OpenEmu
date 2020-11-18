#include <iostream> 
#include <sstream>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h>
#include <thread>
#include <chrono>

#define MAX_CMD_LENGTH     50

std::string get_button_press(){
    do {
        std::cout << '\n' << "Press a key to continue...";
    } while (std::cin.get() != '\n');

    char output[MAX_CMD_LENGTH];
    std::cin.getline(output, MAX_CMD_LENGTH);
    std::string o = output;
    o.erase(o.find_last_not_of(" \n")+1);
    return o;
}

template <typename T>
inline std::string type_to_str(T value) {
    std::stringstream out;
    out << std::fixed;  
    out << value;
    return out.str();
}

std::string get_time(){
    double cur_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() / 1000.;
    std::string cur_time_str = type_to_str(cur_time);
    return cur_time_str;
}

int main(){
    key_t key = ftok("/Users/cinquemb/openemu/OpenEmu/nfbMemoryBridge", 'a');
    int shmid = shmget(key,1024,0666|IPC_CREAT); 
    char *str = (char*) shmat(shmid, NULL , 0);

    /* 
            NDSInputID_R: 8
            NDSInputID_L: 9
            NDSInputID_X: 10
            NDSInputID_Y: 11
            NDSInputID_A: 0
            NDSInputID_B: 1
            NDSInputID_Start: 3
            NDSInputID_Select: 2
            NDSInputID_Up: 6
            NDSInputID_Down: 7
            NDSInputID_Left: 5
            NDSInputID_Right: 4

        626537311337.967, eventType: 3, cookieKey:42, axis:2, axisDirection:2, axisValue:, buttonNumber:2, buttonState:2, hatSwitchType:2, hatDirection:2, keyState:2, keyCode:2
        timestring (in ms) : 626537333986.13, eventType: 2, cookieKey:21, axis:2, axisDirection:, axisValue:, buttonNumber:2, buttonState:, hatSwitchType:2, hatDirection:, keyState:, keyCode:2

        eventType: 4, cookieKey:0, axis:82, axisDirection:1, axisValue:, buttonNumber:82, buttonState:1, hatSwitchType:82, hatDirection:1, keyState:1, keyCode:82
    */
    std::string str_rest = ",4,0,82,1,null,82,1,82,1,1,";
    std::cout << shmid << std::endl;
    //shmdt(str);
    while (true) {
        std::string outstring = str_rest + get_button_press();
        strcpy(str, (get_time() + outstring).c_str());
        std::cout << (get_time() + outstring) << std::endl;
    }
} 