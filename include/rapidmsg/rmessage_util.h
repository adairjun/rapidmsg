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

/* 根据Request来创建一个Response，如果pResponse为NULL，需要调用FreeMssage释放返回的消息句柄
 */
void MakeResponse(const ::rapidmsg::RMessage& pReq, int messageType_, ::rapidmsg::RMessage& pRes);

/*
 * 获取得到debug信息
 */
string DebugString(const ::rapidmsg::RMessage& pReq);

/*
 * 使用protobuf的GetReflection动态设置字段的值
 */
/*
 * 从已经序列化的消息当中取出一个在proto文件当中定义的字段
 * 比如
 * message test{
 *   require string ip = 1;
 *   require uint32 port = 2;
 * }
 * 对于test这个message，这个函数能将序列化之后的string当中获取字段ip或者port的值
 */

string GetStringFieldByMessage(const string& messageType, const string& message, const string& fieldName);

#endif /* _RMESSAGE_UTIL_H_ */
