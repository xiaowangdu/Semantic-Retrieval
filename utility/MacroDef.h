#pragma once

//#define DEBUG 

#ifdef DEBUG
#include <QPointF>
#include "iostream"
using namespace std;
#endif

#define SINGLE_SLOT_CONNECT(Emit_obj, Single, Rec_obj, Slot) \
QObject::connect(Emit_obj, SIGNAL(Single), Rec_obj, SLOT(Slot))

#define EXPORT_UI_SECTION_START(SectionName)  __##SectionName##__{

#define EXPORT_UI_SECTION_END }

#define IMPORT_UI_SECTION_START(SectionName) 
//#ifdef __##SectionName##__

#define IMPORT_UI_SECTION_END #endif


#define DISABLE_COPY(Class)\
Class(const Class &); \
Class& operator = (const Class &)

#define DEFINE_CLASS_PROPERTY(Type, Property) \
public:\
Type get##Property() const {return Property;} \
void set##Property(const Type &p){Property = p;} \
private:\
Type Property

#define DEFINE_CLASS_PROPERTY_DEFAULT(Type, Property, Default) \
public:\
Type get##Property() const{return Property;} \
void set##Property(const Type &p){Property = p;} \
private:\
Type Property = Default


//#define ASSERT(cond) ((!(cond)) ? qt_assert(#cond,__FILE__,__LINE__) : qt_noop())  


#ifdef DEBUG
//example
class Widget {
public:
	Widget() {}
	Widget(const Widget &) {}

	void create() { p = new int(2); }

	void print() {
		cout << *(p) << endl;
	}

	QPointF *makePoint() {
		QPointF * p = new QPointF(1.0, 2.9);
		return p;
	}

private:
	int *p;

private:
	//DISABLE_COPY(widget);
};
#endif