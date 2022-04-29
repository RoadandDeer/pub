#ifndef _CONTROL_PANEL_SDK_H_
#define _CONTROL_PANEL_SDK_H_

#define MAX_HTTP_REPLY 256000
#define MIN_HTTP_REPLY 128000

#define KEY_SCENES          "scenes"
#define KEY_ID			    "id"
#define KEY_DEVICESTATUS    "deviceStatus"
#define KEY_DEVICEPROPERTY  "deviceProperty"
#define KEY_STATUS          "status"
#define KEY_SN 				"sn"
#define KEY_LOADEDDEVICE	"loadedDevices"
#define KEY_LOADEDDEVICEID  "loadedDeviceId"
#define KEY_LOADNAME 		"loadName"
#define KEY_ZONENAME 		"zoneName"
#define KEY_VERSION 		"version"
#define KEY_ZONES			"zones"
#define KEY_FLOOR			"floor"
#define KEY_ADDRESS			"address"
#define KEY_PRODUCTID		"productId"
#define KEY_ACTION			"action"
#define	KEY_IDENTIFIER		"identifier"
#define	KEY_DESCRIPTION		"description"
#define	KEY_DEFAULTMESSAGE	"defaultMessage"
#define	KEY_OPTION			"options"
#define	KEY_RANGE			"range"
#define	KEY_PROPERTIES		"properties"
#define	KEY_VALUE			"value"
#define KEY_DEVICES			"devices"
#define	KEY_MIN				"min"
#define KEY_MAX				"max"
#define KEY_DATA			"data"
#define KEY_ELEMENTS		"elements"
#define KEY_ACCESSMODE		"accessMode"
#define KEY_EDITMODE		"editMode"
#define KEY_DESC			"desc"
#define KEY_CODE            "code"
#define KEY_RESULT          "result"
#define KEY_SCENEID         "sceneId"
#define KEY_ZONEID			"zoneId"
#define KEY_NAME 			"name"
#define KEY_TYPE			"type"


#ifdef __cplusplus
extern "C" {
#endif



/**
 * @brief	结果回调函数
 * @param	result:结果信息
 * @return  
 */
typedef void (*ResultCallback)(char* result);

/**
 * @brief	上报回调函数
 * @param	address:设备地址
 * @param	identifier:属性ID（如果为状态，identifier=status）或者指令ID，事件类型
 * @param	value:属性值、指令内容或事件参数
 * @return  
 */
typedef void (*ReportCallback)(char* address, char* identifier, char* value);


typedef struct Callback_type {
	ReportCallback properties_callback;
	ReportCallback status_callback;
	ReportCallback event_callback;
	ReportCallback command_callback;
}Callback_type;

/**
 * @brief	设置上报回调函数
 * @param	properties_callback:属性上报回调函数
 * @param status_callback:状态上报回调函数
 * @param	event_callback:事件上报回调函数
 * @param	command_callback:控制指令上报回调函数
 * @return  
 */
void setCallback(ReportCallback properties_callback, ReportCallback status_callback, \
ReportCallback event_callback, ReportCallback command_callback);


/**
 * @brief	预初始化发送udp发现广播创建recvudp线程接收广播回复，并将回复信息通过回调函数返回UI
 * @param	broadcast_reply_callback:返回中控回复信息
 * @return  
 */
void smarthome_preinit(ResultCallback broadcast_reply_callback);

/**
 * @brief	初始化创建listening线程
 * @param location  选择的中控ip和port信息
 * @param usn 选择到中控sn
 * @param	link_callback:返回和中控连接结果
 * @return  
 */
void smarthome_init(char* location, char* usn, ResultCallback link_callback);




/**
 * @brief	控制设备(单个)
 * @param	address:要控制的设备地址
 * @param	identifier:要做的动作名称
 * @param	value:动作的值
 * @param	control_callback:返回http请求结果
 * @return  
 */
void smarthome_single_device_control(char* address, char* identifier, char* value, ResultCallback control_callback);


/**
 * @brief	控制设备(可批量)
 * @param	control_msg:控制信息
 * @param	control_callback:返回http请求结果
 * @return  
 */
void smarthome_device_control(char* control_msg, ResultCallback control_callback);


/**
 * @brief	UI主动请求更新所有配置信息
 * @param	configurations_msg:配置信息字符串接收数组
 * @return  
 */
void smarthome_all_configurations_update(char *configurations_msg);

/**
 * @brief	UI主动请求更新所有场景信息
 * @param	scenes_msg:场景信息字符串接收数组
 * @param flag:flag=0获取简单信息,否则获取详细信息
 * @return  
 */
void smarthome_all_scenes_update(char* scenes_msg, int flag);


/**
 * @brief	UI主动请求更新指定配置信息(可批量)
 * @param	configurations_msg:指定配置信息字符串接收数组
 * @param	param:指定设备信息
 * @return  
 */
void smarthome_configurations_update(char* configurations_msg, char* param);


/**
 * @brief	UI主动请求更新指定属性信息(可批量)
 * @param	properties_msg:指定属性信息字符串接收数组
 * @param	address:指定设备地址
 * @return  
 */
void smarthome_properties_update(char* properties_msg, char* address);

/**
 * @brief	UI主动请求更新指定状态信息(可批量)
 * @param	status_msg:指定状态信息字符串接收数组
 * @param	address:指定设备地址
 * @return  
 */
void smarthome_status_update(char* status_msg, char* address);

/**
 * @brief	控制场景
 * @param	sceneId:要控制的场景ID
 * @return  
 */
void smarthome_scene_control(char* sceneId);

/**
 * @brief	取消UDP监听线程
 * @return  
 */
void smarthome_cancel_udp_recv_pthread();

/**
 * @brief	清除缓存
 * @return  
 */
void smarthome_clean_all_buffer();

/**
 * @brief	设置UDP监听端口
 * @param	port:端口号
 * @return  
 */
void smarthome_set_listen_port(int port);

#ifdef __cplusplus
}
#endif

#endif