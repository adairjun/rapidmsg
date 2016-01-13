#include "rapidmsg/rmessage_util.h"
#include <google/protobuf/descriptor.h>
#include <google/protobuf/dynamic_message.h>

/*
 * protobuf反射
 */
google::protobuf::Message* CreateMessage(const string& type_name) {

  google::protobuf::Message* message = NULL;
  const google::protobuf::Descriptor* descriptor =
	    google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(type_name);

  if (descriptor) {
    const google::protobuf::Message* prototype =
	      google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
	if (prototype) {
	  message = prototype->New();
	}
  }
  return message;
}


/**
 * 根据请求包构造应答包的消息头
 **/
void MakeResponse(const ::rapidmsg::RMessage *pReq, int messageType_, ::rapidmsg::RMessage *pRes) {

  if (pReq == NULL || !pReq->has_head()) {
    LOG(ERROR) << " pReq is null pointer or don't have head\n";
  }
  if (pRes == NULL) {
    LOG(ERROR) << "pRes is null pointer\n";
  }

  if (pReq->head.has_session_no()) { pRes->mutable_head()->set_session_no(pReq->head.session_no()); }

  pRes->mutable_head()->set_message_type(messageType_);

  if (pReq->head.has_client_ip()) { pRes->mutable_head()->set_client_ip(pReq->head.client_ip()); }
  if (pReq->head.has_target_ip()) { pRes->mutable_head()->set_target_ip(pReq->head.target_ip()); }
  if (pReq->head.has_target_port()) { pRes->mutable_head()->set_target_port(pReq->head.target_port()); }
}
