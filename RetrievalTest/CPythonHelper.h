#ifndef CPYTHONHELPER_H
#define CPYTHONHELPER_H
#include "Python.h"
#include <functional>
#include <iostream>
#include <QString>
#include <string>

namespace pystd
{
typedef std::function<void(std::string)> StdoutWritePointer;

struct Stdout
{
    PyObject_HEAD
    StdoutWritePointer write;
};


class CPythonHelper
{
public:
    static CPythonHelper *getInstance();

    void setStdout(StdoutWritePointer write);
    void resetStdout();

    PyObject *processPyEvt(const QString &modulePath,
                      const QString &moduleName,
                      const QString &callFun, PyObject *pArg,
                      StdoutWritePointer writer);

private:
    CPythonHelper();
    ~CPythonHelper();
    CPythonHelper(const CPythonHelper&){}
    CPythonHelper& operator=(const CPythonHelper&){}

private:
    static CPythonHelper* m_instance;
};

PyObject* stdoutWrite(PyObject* self, PyObject* args);
PyObject* stdoutFlush(PyObject* /*self*/, PyObject* /*args*/);

PyMODINIT_FUNC PyInit_pystd(void);
void setStdout(StdoutWritePointer write);
void resetStdout();

PyObject *processPyEvt(const QString &modulePath,
                  const QString &moduleName,
                  const QString &callFun, PyObject *pArg,
                  StdoutWritePointer writer);
} // namespace pystd

#endif // CPYTHONHELPER_H
