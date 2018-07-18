#include "Exception.hpp"
#include <QDebug>

Exception::Exception()
{
	
}

Exception::~Exception()
{
	
}

void Exception::printMessage()
{
	qDebug() << "exception occur.";
}

MemoryException::MemoryException(const QString &msg, QObject * whose) 
{ 
	m_exceptionMsg = (QString("__%1__ memory operate exception: %2").arg(whose->objectName()).arg(msg));
}

void MemoryException::printMessage()
{
	qDebug() << m_exceptionMsg;
}