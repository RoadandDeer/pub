#include "control_panel_sdk.h"
#include "stdio.h"
#include "string.h"
#include "pthread.h"
#include <unistd.h>
#include <stdlib.h>


static int listening_quit = 0;

typedef struct MSG
{
	char address[BUFLEN_32];
	char identifier[BUFLEN_32];
	char value[BUFLEN_1024];
	MSG_TYPE type; 
}MSG;


typedef struct Callback_type {
	CallbackFunc properties_callback;
	CallbackFunc status_callback;
	CallbackFunc event_callback;
	CallbackFunc metrics_callback; 
	CallbackFunc command_callback;
}Callback_type;

static Callback_type* Callback_type_t;

void setCallback(CallbackFunc properties_callback, CallbackFunc status_callback, CallbackFunc event_callback, CallbackFunc metrics_callback, CallbackFunc command_callback){
	Callback_type_t = malloc(sizeof(Callback_type));
    memset(Callback_type_t, 0, sizeof(Callback_type));
	Callback_type_t->properties_callback = properties_callback;
	Callback_type_t->status_callback = status_callback;
	Callback_type_t->event_callback = event_callback;
	Callback_type_t->metrics_callback = metrics_callback;
	Callback_type_t->command_callback = command_callback;
}


void smarthome_device_control(char* address, char* identifier, char* value) {
    //向中控发送控制信息
	printf("完成设备控制！ address = %s, identifier = %s, value = %s\n",address,identifier,value);
	return;
}


void smarthome_all_configurations_update(char *configurations_msg) {
   char *configurations_result = 
    	"{\"version\":\"1\",\"name\":\"DiscoveryLoadedDevicesResponse\",\"loadedDevices\":"
        "[{\"sn\":\"D820020934D84D371\",\"loadedDeviceId\":\"5vcn7GFceDitdP0UouG3Nb\",\""
        "address\":\"20934D84D371\",\"productId\":\"129\",\"action\":[],\"loadName\":\"ac\","
        "\"type\":\"53\",\"zoneId\":\"5lJLCAuPxxZg69YUHjcdl5\",\"floor\":\"1\",\"zoneName\":"
        "\"卧室\"},{\"sn\":\"D820020934D84D371\",\"loadedDeviceId\":\"5S5J4qKvA6PCoS9rhm2ibD\""
        ",\"address\":\"804B50FFFEF411B2-1\",\"productId\":\"4\",\"action\":[{\"identifier\":"
        "\"PowerSwitch\",\"defaultMessage\":\"开关\",\"options\":[{\"value\":\"0\",\"desc\":"
        "\"关\"},{\"value\":\"1\",\"desc\":\"开\"}]},{\"identifier\":\"ToggleSwitch\",\""
        "defaultMessage\":\"翻转\"}],\"loadName\":\"11b2 1\",\"type\":\"1\",\"zoneId\":\""
        "5lJLCAuPxxZg69YUHjcdl5\",\"floor\":\"1\",\"zoneName\":\"卧室\"}]}";
	strcpy(configurations_msg,configurations_result);
	printf("全部配置已传回\n");
	return ;    
}

void smarthome_all_scenes_update(char* scenes_msg) {
    char *scenes_result = 
		"{\"scenes\":[{\"sn\":\"D820020934D84D371\",\"sceneId\":1,\"name\":\"开\","
		"\"protocol\":1,\"type\":3,\"zoneId\":\"5lJLCAuPxxZg69YUHjcdl5\"}]}";
	strcpy(scenes_msg , scenes_result);  
	printf("全部场景已传回\n");  
	return;
}

// void smarthome_all_properties_update(char* properties_msg) {
//     char *properties_result= 
// 		"{\"properties\":[{\"name\":\"HardVersion\",\"value\":\"2.0\"},"
// 		"{\"name\":\"HostVersion\",\"value\":\"06040104\"},{\"name\":\"NcpVersion\",\"value\":\"6.4.0-385\"}]}";
// 	strcpy(properties_msg,properties_result);
// 	return;
// }

// void smarthome_all_status_update(char* status_msg) {
//     char *status_result= 
// 		"{\"properties\":[{\"name\":\"HardVersion\",\"value\":\"2.0\"},"
// 		"{\"name\":\"HostVersion\",\"value\":\"06040104\"},{\"name\":\"NcpVersion\",\"value\":\"6.4.0-385\"}]}";
// 	strcpy(status_msg,status_result);
// 	return;
// }





void smarthome_configurations_update(char *configurations_msg, char* address){
	char *configurations_result = 
		"{\"sn\":\"D820020934D84D371\",\"loadedDeviceId\":\"5vcn7GFceDitdP0UouG3Nb\",\""
        "address\":\"20934D84D371\",\"productId\":\"129\",\"action\":[],\"loadName\":\"ac\","
        "\"type\":\"53\",\"zoneId\":\"5lJLCAuPxxZg69YUHjcdl5\",\"floor\":\"1\",\"zoneName\":"
        "\"卧室\"}";
	strcpy(configurations_msg, configurations_result);
	printf("指定配置address = %s已传回\n",address);
	return;
}

void smarthome_properties_update(char* properties_msg, char* address) {
    char *properties_result =
		"{\"properties\":[{\"name\":\"HardVersion\",\"value\":\"2.0\"},"
		"{\"name\":\"HostVersion\",\"value\":\"06040104\"},{\"name\":\"NcpVersion\",\"value\":\"6.4.0-385\"}]}";
	strcpy(properties_msg,properties_result);
	printf("指定属性address = %s已传回\n",address);
	return;
}

void smarthome_status_update(char* status_msg, char* address) {
	char *status_result= "{\"status\":\"0\"}";
	strcpy(status_msg , status_result);
	printf("指定状态address = %s已传回\n",address);
	return;
}

void smarthome_scenes_update(char* scenes_msg, char* sceneId) {
	char *scenes_result = 
		"{\"sceneId\":1,\"name\":\"开\",\"type\":3,\"zoneId\":\"5lJLCAuPxxZg69YUHjcdl5\"}";
	strcpy(scenes_msg , scenes_result);
	printf("指定场景sceneId = %s已传回\n",sceneId);
	return;
}

//信息解析函数
static void smarthome_msg_parsing(){
	MSG *msg_t = (struct MSG*)malloc(sizeof(MSG));

	//解析给MSG结构体赋值
	for (int i = 0; i < 10; i++)
	{
		sprintf(msg_t->address, "002396%d", i);
		sprintf(msg_t->identifier, "zhongkong%d", i);
		sprintf(msg_t->value, "value%d", i);
		msg_t->type = i%5+1;

		//根据msg_t->type调用callback
		switch (msg_t->type)
		{
		case PROPERTIES:
			printf("PROPERTIES:	");
			Callback_type_t->properties_callback(msg_t->address, msg_t->identifier, msg_t->value);
			break;
		case STATUS:
			printf("STATUS:	");
			Callback_type_t->status_callback(msg_t->address, msg_t->identifier, msg_t->value);
			break;
		case EVENT:
			printf("EVENT:	");
			Callback_type_t->event_callback(msg_t->address, msg_t->identifier, msg_t->value);
			break;
		case METRICS:
			printf("METRICS:	");
			Callback_type_t->metrics_callback(msg_t->address, msg_t->identifier, msg_t->value);
			break;
		case COMMAND:
			printf("COMMAND:	");
			Callback_type_t->command_callback(msg_t->address, msg_t->identifier, msg_t->value);
			break;
		default:
			printf("-------\n");
			break;
		}
	}

	
}

static void* listening(void *arg) {
	
	//循环监听信息
	while(!listening_quit)
	{
		sleep(2);
		//如果接受到信息
		if(1 > 0)
		{
			//调用信息解析函数
			smarthome_msg_parsing();
			listening_quit = 1;
		}
		
	}
	return NULL;
}


void smarthome_init() {
	logh;
	pthread_t t1;
    pthread_create(&t1, NULL, &listening, NULL);
	return;
}

