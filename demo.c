#include "control_panel_sdk.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 10240
#define MIN_SIZE 128

int flag = 0;

void control_callback(char* result){
    printf("control result: %s\n",result);
    return;
}
void link_callback(char* result){
    printf("link result: %s\n",result);
    return;
}

void broadcast_reply_callback(char* result) {
    printf("broadcast result: \n%s\n",result);
    flag = 1;
    return;
}

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

void command_callback(char* addr, char* identifier, char* value){    
    printf("command_callback: addr = %s, identifier = %s, value = %s\n",addr,identifier,value);
    return;
}

int main(){

    //预初始化，获取所有中控信息
    smarthome_preinit(broadcast_reply_callback);
    while(!flag){};

    //初始化，传入需要连接的中控信息
    smarthome_init("LOCATION: http://192.168.10.1:8085", "USN: 562002875D8062FFA",link_callback);

    //设置上报回调函数
    setCallback(properties_callback,status_callback,event_callback,command_callback);

    char configurations_msg[MAX_SIZE];  
    char scenes_msg[MAX_SIZE];
    char appoint_configurations_msg[128];
    char appoint_properties_msg[128];
    char appoint_status_msg[128];

    //获取全部配置
    smarthome_all_configurations_update(configurations_msg);
    printf("configurations_msg = %s\n",configurations_msg);
    
    //获取全部场景详细信息
    smarthome_all_scenes_update(scenes_msg,1);
    printf("scenes_msg = %s\n",scenes_msg);

    //获取全部场景简单信息
    smarthome_all_scenes_update(scenes_msg,0);
    printf("scenes_msg = %s\n",scenes_msg);
    
    //执行场景
    smarthome_scene_control("1");
     
    //控制单个设备 
    smarthome_single_device_control("EC1BBDFFFEBAC618-1","PowerSwitch","0",control_callback);

    //控制多个设备
    char con[] = 
        "{\"devices\":[{\"address\":\"EC1BBDFFFEBAC618-1\",\"identifier\":\"PowerSwitch\",\"value\":\"0\"},"
        "{\"address\":\"addr2\",\"identifier\":\"PowerSwitch\",\"value\":\"1\"}]}";
    smarthome_device_control(con,control_callback);

    //获取指定设备在线状态
    smarthome_status_update(appoint_status_msg,"{\"deviceStatus\":[{\"address\":\"EC1BBDFFFEBAC618-1\"},{\"address\":\"addr\"}]}");
    printf("appoint_status_msg = %s\n",appoint_status_msg);

    //获取指定设备属性
    char a[] = "{\"deviceProperty\": [{\"address\":\"EC1BBDFFFEBAC618-1\"},{\"address\":\"addr2\"}]}"; 
    smarthome_properties_update(appoint_properties_msg,a);
    printf("appoint_properties_msg = %s\n",appoint_properties_msg);

   //获取指定设备信息
    smarthome_configurations_update(appoint_configurations_msg,"{\"zoneId\":[\"2gDRR1mhgl55d1kgRnBHQ0\"],\"type\":[\"1\"]}");
    printf("appoint_configurations_msg = %s\n",appoint_configurations_msg);

    while (1)
    {
        
    }
    
    return 0;
}