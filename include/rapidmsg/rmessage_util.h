#ifndef _RMESSAGE_UTIL_H_
#define _RMESSAGE_UTIL_H_

#include <string>

using std::string;

// 利用protobuf自动反射消息类型来创建一个message对象
// 需要手动delete
template<typename T>
T* NewEmptyMessageWithName();

#endif
