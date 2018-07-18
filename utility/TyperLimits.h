#pragma once
#include "TypeAdapter.h"

template<class T> struct __StaticCheck_1 {
	__StaticCheck_1(...) {}
};

template<> struct __StaticCheck_1<TypeAt<5, typelist>::type> {};
template<> struct __StaticCheck_1<TypeAt<6, typelist>::type> {};

#define STATIC_CHECK(expr, msg) { \
	class Error_##msg {};  \
	sizeof((__StaticCheck_1<expr>(Error_##msg())));\
}

template<class Type> void NOT_IS_ALLOWED_TYPE_CHECK(Type t) {
	STATIC_CHECK(Type, AssertAllow);
}

template<class T> struct __StaticCheck_2 {
	__StaticCheck_2(TypeAt<4, typelist>::type) {}
	__StaticCheck_2(TypeAt<5, typelist>::type) {}
	__StaticCheck_2(TypeAt<6, typelist>::type) {}
};

template<class Type> void IS_ALLOWED_TYPE_CHECK(Type t) {
	__StaticCheck_2<Type> __er__(t);
}