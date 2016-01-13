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

string DebugString(const ::rapidmsg::RMessage& pReq) {
  return pReq.DebugString();
}
