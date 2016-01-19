#ifndef _RMESSAGE_UTIL_H_
#define _RMESSAGE_UTIL_H_

#include "rapidmsg.pb.h"
#include <string>
#include <boost/shared_ptr.hpp>

using std::string;

boost::shared_ptr<::rapidmsg::RMessage> NewMessage(const string& session_no,
		int message_type);

/*
 *  利用protobuf自动反射消息类型来创建一个message对象
 *  需要手动delete
 *  返回的google::protobuf::Message* 可以利用dynamic_cast<>来转换成对应的message的类型
 */
boost::shared_ptr<::google::protobuf::Message> CreateMessage(const string& type_name);

/*
 * 从已经序列化的消息当中反序列化
 */
boost::shared_ptr<::google::protobuf::Message> ParseFromStr(const string& messageType, const string& message);

/* 根据Request来创建一个Response，如果pResponse为NULL，需要调用FreeMssage释放返回的消息句柄
 */
void MakeResponse(const ::rapidmsg::RMessage& pReq, int messageType_, ::rapidmsg::RMessage& pRes);

/*
 * 获取得到debug信息
 */
string DebugString(const ::rapidmsg::RMessage& pReq);

int32_t GetInt32FieldByPointer(boost::shared_ptr<::google::protobuf::Message> new_obj, const string& fieldName, int index);
uint32_t GetUInt32FieldByPointer(boost::shared_ptr<::google::protobuf::Message> new_obj, const string& fieldName, int index);

int64_t GetInt64FieldByPointer(boost::shared_ptr<::google::protobuf::Message> new_obj, const string& fieldName, int index);
uint64_t GetUInt64FieldByPointer(boost::shared_ptr<::google::protobuf::Message> new_obj, const string& fieldName, int index);

float GetFloatFieldByPointer(boost::shared_ptr<::google::protobuf::Message> new_obj, const string& fieldName, int index);
double GetDoubleFieldByPointer(boost::shared_ptr<::google::protobuf::Message> new_obj, const string& fieldName, int index);

bool GetBoolFieldByPointer(boost::shared_ptr<::google::protobuf::Message> new_obj, const string& fieldName, int index);
string GetStringFieldByPointer(boost::shared_ptr<::google::protobuf::Message> new_obj, const string& fieldName, int index);


#endif /* _RMESSAGE_UTIL_H_ */
