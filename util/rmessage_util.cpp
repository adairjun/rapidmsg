#include "rapidmsg/rmessage_util.h"
#include <google/protobuf/descriptor.h>
#include <google/protobuf/dynamic_message.h>

template<typename T>
T* NewEmptyMessageWithName() {

  string type_name = T::descriptor()->full_name();
  const google::protobuf::Descriptor* descriptor =
	    google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(type_name);

  const google::protobuf::Message* prototype =
      google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
  T* new_obj = dynamic_cast<T*>(prototype->New());
  return new_obj;
}

