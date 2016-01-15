#include "rapidmsg/rmessage_util.h"
#include <google/protobuf/descriptor.h>
#include <google/protobuf/dynamic_message.h>

boost::shared_ptr<::rapidmsg::RMessage> NewMessage(const string& session_no,
		int message_type) {
  boost::shared_ptr<::rapidmsg::RMessage> pMessage(new ::rapidmsg::RMessage);
  pMessage->mutable_head()->set_session_no(session_no);
  pMessage->mutable_head()->set_message_type(message_type);

  return pMessage;
}

/*
 * protobuf反射
 */
boost::shared_ptr<::google::protobuf::Message> CreateMessage(const string& type_name) {

  const google::protobuf::Descriptor* descriptor =
	    google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(type_name);

  if (descriptor) {
    const google::protobuf::Message* prototype =
	      google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
	if (prototype) {
		boost::shared_ptr<::google::protobuf::Message> message(prototype->New());
	    return message;
	}
  }
  throw std::runtime_error("Can't CreateMessage");
}


/**
 * 根据请求包构造应答包的消息头
 **/
void MakeResponse(const ::rapidmsg::RMessage& pReq, int messageType_, ::rapidmsg::RMessage& pRes) {

  if (!pReq.has_head()) {
	return;
  }

  // request是什么session_no，就响应什么session_no。因为一个回话session势必有request和response
  if (pReq.head().has_session_no()) { pRes.mutable_head()->set_session_no(pReq.head().session_no()); }

  pRes.mutable_head()->set_message_type(messageType_);

  // 反转client以及target，request的client是response的target
  if (pReq.head().has_client_ip()) { pRes.mutable_head()->set_target_ip(pReq.head().client_ip()); }
  if (pReq.head().has_client_port()) { pRes.mutable_head()->set_target_port(pReq.head().client_port()); }

  if (pReq.head().has_target_ip()) { pRes.mutable_head()->set_client_ip(pReq.head().target_ip()); }
  if (pReq.head().has_target_port()) { pRes.mutable_head()->set_client_port(pReq.head().target_port()); }
}

/*
 * 这仅仅只是简单地调用DebugString，任何一个::protobuf::Message的对象都可以，这里把它封装进来的原因是为了限制参数只能是::rapidmsg::RMessage
 */
string DebugString(const ::rapidmsg::RMessage& pReq) {
  return pReq.DebugString();
}

string GetStringFieldByMessage(const string& messageType, const string& message, const string& fieldName) {

  const ::google::protobuf::Descriptor* descriptor = ::google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(messageType);
  const ::google::protobuf::Message* prototype = ::google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
  boost::shared_ptr<google::protobuf::Message> new_obj(prototype->New());
  new_obj->ParseFromString(message);

  const ::google::protobuf::Reflection* reflection = new_obj->GetReflection();
  const ::google::protobuf::FieldDescriptor* rmes_field = descriptor->FindFieldByName(fieldName);
  return reflection->GetString(*new_obj, rmes_field);

  /*if (typeid(T) == typeid(int32_t)) {
	return reflection->GetInt32(*new_obj, rmes_field);
  } else if (typeid(T) == typeid(int64_t)) {
	return reflection->GetInt64(*new_obj, rmes_field);
  } else if (typeid(T) == typeid(uint32_t)) {
  	return reflection->GetUInt64(*new_obj, rmes_field);
  } else if (typeid(T) == typeid(uint64_t)) {
  	return reflection->GetUInt64(*new_obj, rmes_field);
  } else if (typeid(T) == typeid(float)) {
  	return reflection->GetFloat(*new_obj, rmes_field);
  } else if (typeid(T) == typeid(double)) {
  	return reflection->GetDouble(*new_obj, rmes_field);
  } else if (typeid(T) == typeid(bool)) {
  	return reflection->GetBool(*new_obj, rmes_field);
  } else if (typeid(T) == typeid(string)) {
  	return reflection->GetString(*new_obj, rmes_field);
  } else {
	// 如果什么类型都没匹配上，那么默认构造一个T，然后返回它
	T t;
	return t;
  }*/
}
