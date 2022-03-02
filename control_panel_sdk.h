#ifndef _CONTROL_PANEL_SDK_H_
#define _CONTROL_PANEL_SDK_H_

#define BUFLEN_1024 1024
#define BUFLEN_256 256
#define BUFLEN_64 64
#define BUFLEN_128 128
#define BUFLEN_32 32
#define BUFLEN_16 16

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  PROPERTIES = 1,
  STATUS,
  EVENT,
  METRICS,
  COMMAND,
}MSG_TYPE;


/**
 * @brief	初始化创建listening线程
 * @return  
 */
void smarthome_init();


/**
 * @brief	上报回调函数
 * @param	address：设备地址
 * @param	identifier：属性ID（如果为状态，identifier=status）或者指令ID，事件类型
 * @param	value:属性值、指令内容或事件参数
 * @return  
 */
typedef void (*CallbackFunc)(void* address, void* identifier, void* value);

/**
 * @brief	设置回调函数
 * @param	properties_callback:属性上报回调函数
 * @param status_callback:状态上报回调函数
 * @param	event_callback:事件上报回调函数
 * @param	metrics_callback:ZigBee指标上报回调函数
 * @param	command_callback:控制指令上报回调函数
 * @return  
 */
void setCallback(CallbackFunc properties_callback, CallbackFunc status_callback, \
CallbackFunc event_callback, CallbackFunc metrics_callback, CallbackFunc command_callback);



/**
 * @brief	控制设备
 * @param	address：要控制的设备地址
 * @param	identifier：要做的动作名称
 * @param	value：动作的值
 * @return  
 */
void smarthome_device_control(char* address, char* identifier, char* value);





/**
 * @brief	UI主动请求更新所有配置信息
 * @param	configurations_msg：配置信息字符串接收数组
 * @return  
 */
void smarthome_all_configurations_update(char *configurations_msg);

/**
 * @brief	UI主动请求更新所有场景信息
 * @param	scenes_msg:场景信息字符串接收数组
 * @return  
 */
void smarthome_all_scenes_update(char* scenes_msg);

/**
 * @brief	UI主动请求更新所有属性信息
 * @param	properties_msg:属性信息字符串接收数组
 * @return  
 */
//void smarthome_all_properties_update(char* properties_msg);

/**
 * @brief	UI主动请求更新所有状态信息
 * @param	status_msg:状态信息字符串接收数组
 * @return  
 */
//void smarthome_all_status_update(char* status_msg);





/**
 * @brief	UI主动请求更新指定配置信息
 * @param	configurations_msg:指定配置信息字符串接收数组
 * @param address:指定设备地址
 * @return  
 */
void smarthome_configurations_update(char* configurations_msg, char* address);

/**
 * @brief	UI主动请求更新指定场景信息
 * @param	scenes_msg:指定场景信息字符串接收数组
 * @param sceneId:指定场景ID
 * @return  
 */
void smarthome_scenes_update(char* scenes_msg, char* sceneId) ;

/**
 * @brief	UI主动请求更新指定属性信息
 * @param	properties_msg:指定属性信息字符串接收数组
 * @param address:指定设备地址
 * @return  
 */
void smarthome_properties_update(char* properties_msg, char* address);

/**
 * @brief	UI主动请求更新指定状态信息
 * @param	status_msg:指定状态信息字符串接收数组
 * @param address:指定设备地址
 * @return  
 */
void smarthome_status_update(char* status_msg, char* address) ;





#include <time.h>

#define logh                                                                     \
  do {                                                                           \
    char tmpBuf[16];                                                             \
    time_t t = time(NULL);                                                       \
    strftime(tmpBuf, 16, "\033[31m%m-%d %H:%M:%S", localtime((const long*)&t));  \
    fprintf(stdout, "%s H/%-20s: line:%d\n\033[0m", tmpBuf, __FILE__, __LINE__); \
  } while (0)

#ifdef __cplusplus
}
#endif

#endif