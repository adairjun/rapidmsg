#ifndef _RMESSAGE_UTIL_H_
#define _RMESSAGE_UTIL_H_

#include "rapidmsg.pb.h"
#include <string>

using std::string;

/*
 *  利用protobuf自动反射消息类型来创建一个message对象
 *  需要手动delete
 *  返回的google::protobuf::Message* 可以利用dynamic_cast<>来转换成对应的message的类型
 */
google::protobuf::Message* CreateMessage(const string& type_name);

// 根据Request来创建一个Response，如果pResponse为NULL，需要调用FreeMssage释放返回的消息句柄
void MakeResponse(const ::rapidmsg::RMessage *pReq, int messageType_, ::rapidmsg::RMessage *pRes);

#endif /* _RMESSAGE_UTIL_H_ */
