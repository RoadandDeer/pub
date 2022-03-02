#include "control_panel_sdk.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 10240
#define MIN_SIZE 128

void properties_callback(char* addr, char* identifier, char* value) {
    printf("properties_callback: addr = %s, identifier = %s, value = %s\n",addr,identifier,value);
    return;
}

void status_callback(char* addr, char* identifier, char* value){
    printf("status_callback: addr = %s, identifier = %s, value = %s\n",addr,identifier,value);
    return;
}
void event_callback(char* addr, char* identifier, char* value){
    printf("event_callback: addr = %s, identifier = %s, value = %s\n",addr,identifier,value);
    return;
}
void metrics_callback(char* addr, char* identifier, char* value){
    printf("metrics_callback: addr = %s, identifier = %s, value = %s\n",addr,identifier,value);
    return;

}
void command_callback(char* addr, char* identifier, char* value){    
    printf("command_callback: addr = %s, identifier = %s, value = %s\n",addr,identifier,value);
    return;
}

int main(){

    smarthome_init();
    setCallback(properties_callback,status_callback,event_callback,metrics_callback,command_callback);
    char configurations_msg[MAX_SIZE];  
    char scenes_msg[MAX_SIZE];
    char appoint_configurations_msg[128];
    char appoint_properties_msg[128];
    char appoint_scenes_msg[128];
    char appoint_status_msg[128];
    smarthome_all_configurations_update(configurations_msg);//获取全部配置
    smarthome_all_scenes_update(scenes_msg);//获取全部场景
    smarthome_configurations_update(appoint_configurations_msg,"20934D84D371");;
    smarthome_properties_update(appoint_properties_msg,"20934D84D371");
    smarthome_status_update(appoint_status_msg,"20934D84D371");
    smarthome_scenes_update(appoint_scenes_msg,"1");
    smarthome_device_control("dsadad","PowerSwitch","0");//控制设备
    sleep(5);
    printf("configurations_msg = %s\n scenes_msg = %s\n appoint_configurations_msg = %s\n appoint_properties_msg = %s\n appoint_status_msg = %s\n appoint_scenes_msg = %s\n",\
    configurations_msg, scenes_msg,appoint_configurations_msg,appoint_properties_msg,appoint_status_msg,appoint_scenes_msg);
    return 0;
}