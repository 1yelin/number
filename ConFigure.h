#pragma once

//通过编译方式去掉Unicode字符集
#ifdef UNICODE    //如果定义了UNICODE
#undef UNICODE    //就取消UNICODE
#endif // UNICODE

#include <easyx.h>
#include <graphics.h>
#include <string>