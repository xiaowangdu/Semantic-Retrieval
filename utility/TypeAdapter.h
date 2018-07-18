#pragma once
//study ref:https://www.zhihu.com/question/52599971
//source code: Loki


#include <iostream>

template<typename...> struct List {};
template<typename T, typename... U>
struct List<T, U...>
{
	using Head = T;
	using Tail = List<U...>;
};

template<unsigned int, typename> struct TypeAt;
template<> struct TypeAt<0, List<>>
{
	using type = List<>;
};

template<typename Head, typename... Tail>
struct TypeAt<0, List<Head, Tail...>>
{
	using type = Head;
};

template<unsigned int idx, typename Head, typename... Tail>
struct TypeAt<idx, List<Head, Tail...>>
{
	using type = typename TypeAt<idx - 1, List<Tail...>>::type;
};

using typelist = List<int, char*, float, QVector<QString>, QVector<QAction *>, QVector<QMenu *>, QVector<QObject *>>;

#ifdef DEBUG
void testType(int p)
{
	printf("int %d\n", p);
}

void testType(QVector<QString>)
{
	printf("QVector<QString>\n");
}


void testType(char *)
{
	printf("char *\n");
}
#endif