#pragma once
#include <QObject>
#include <QMap>
#include "MacroDef.h"
#include <iostream>

using namespace std;

template <typename ... T>
void __dummy_func__(T... t) {}

template <class T>
T __pack_into_datastream__(QDataStream & stream, const T& t) {
	//note: the type T must have overloaded operator<<
	stream << t;
	return t;
}

template <class T>
T & __unpack_datastream__(QDataStream & stream, T & t) {
	//note: the type T must have overloaded operator>>
	stream >> t;
	return t;
}

template <typename...>
class _Settings {
public:
	template <typename T, typename... Args>
	int new_element(const QString& key, const T& first, const Args& ... data) {
		int element_type_count = sizeof...(data)+1;
		//std::cout << "Key: " << key.toStdString() << std::endl;

		QByteArray *tmparray = new QByteArray();
		QDataStream out(tmparray, QIODevice::WriteOnly);

		__dummy_func__(__pack_into_datastream__(out, data)...);

		out << first;

		if (m_dict.count(key) > 0) {
			std::cout << "Key: " << key.toStdString() << "key name already exist.";
			std::cout << "I will replace it.";
			//return -1;
		}

		m_dict.insert(key, *tmparray);
		delete tmparray;
		return element_type_count;
	}

	template <typename T, typename... Args>
	int modify_element(const QString& key, const T& first, const Args& ... data) {
		return new_element(key, first, data...);
	}

	template <typename T, typename... Args>
	bool decode_element(QByteArray *bytes, T & first, Args & ... data) {
		QDataStream in(bytes, QIODevice::ReadOnly);

		__dummy_func__(__unpack_datastream__(in, data)...);
		
		in >> first;

		if (!in.atEnd()) {
			return false;
		}

		return true;
	}

	int size() const { return m_dict.size(); }
	void deleteElement(const QString &key);
	QByteArray &operator[] (const QString &key);
	const QByteArray operator[](const QString &key) const;

	_Settings<> &operator=(const _Settings<> &other);

	QByteArray& value(const QString &key);
	bool saveAsText(const QString &filepath);
	bool load(const QString &filepath = "");
	bool save(const QString &filepath = "");

private:
	QMap<QString, QByteArray> m_dict;
};

typedef _Settings<> Settings;
