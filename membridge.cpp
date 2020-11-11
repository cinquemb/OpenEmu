#include <iostream> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h>
#include <thread>
#include <chrono>

int main(){ 

    key_t key = ftok("/Users/cinquemb/openemu/OpenEmu/nfbMemoryBridge", 'a');

    int shmid = shmget(key,1024,0666|IPC_CREAT); 

    char *str = (char*) shmat(shmid, NULL , 0);

    /* 
        626537311337.967, eventType: 3, cookieKey:42, axis:2, axisDirection:2, axisValue:, buttonNumber:2, buttonState:2, hatSwitchType:2, hatDirection:2, keyState:2, keyCode:2
        timestring (in ms) : 626537333986.13, eventType: 2, cookieKey:21, axis:2, axisDirection:, axisValue:, buttonNumber:2, buttonState:, hatSwitchType:2, hatDirection:, keyState:, keyCode:2

        eventType: 4, cookieKey:0, axis:82, axisDirection:1, axisValue:, buttonNumber:82, buttonState:1, hatSwitchType:82, hatDirection:1, keyState:1, keyCode:82
    */
    char *str_rest1 = "null";
    char *str_rest2 = "null,3,42,2,2,null,2,2,2,2,2,79";
    char *str_rest3 = "null,4,0,82,1,null,82,1,82,1,1,82";
    std::cout << shmid << std::endl;
    //shmdt(str);
    int alt = 0;
    while (true) {
        if (alt == 0){
            strcpy(str, str_rest3);
            std::string outstring = str;
            std::cout << outstring << std::endl;
            alt = 1;
        }else{
            strcpy(str, str_rest2);
            std::string outstring = str;
            std::cout << outstring << std::endl;
            alt = 0;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
} 