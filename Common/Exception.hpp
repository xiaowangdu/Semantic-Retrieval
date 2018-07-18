#pragma once
#include <QException>
#include <QObject>

class Exception : public QException {
	

public:
	Exception();
	~Exception();

	void raise() const { throw *this; }
	Exception *clone() const { return new Exception(*this); }

	virtual void printMessage();

private:
	
};

class MemoryException : public QException
{
public:
	MemoryException(const QString &msg, QObject * whose);

	QString exception_string() const { return m_exceptionMsg; }
	void printMessage();

private:
	QString m_exceptionMsg;
};