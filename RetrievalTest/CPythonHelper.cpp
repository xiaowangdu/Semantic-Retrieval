#include "CPythonHelper.h"
#include <QDebug>

namespace pystd
{

CPythonHelper* CPythonHelper::m_instance = NULL;
CPythonHelper *CPythonHelper::getInstance()
{
    if(m_instance == NULL){
        if(m_instance == NULL){
            m_instance = new CPythonHelper();
        }
    }

    return m_instance;
}

CPythonHelper::CPythonHelper()
{
    PyImport_AppendInittab("pystd", pystd::PyInit_pystd);
    Py_Initialize();
    PyImport_ImportModule("pystd");
}

CPythonHelper::~CPythonHelper()
{
    Py_Finalize();
    delete m_instance;
}

void CPythonHelper::setStdout(StdoutWritePointer write)
{
    pystd::setStdout(write);
}

void CPythonHelper::resetStdout()
{
    pystd::resetStdout();
}

PyObject * CPythonHelper::processPyEvt(const QString &modulePath,
                                       const QString &moduleName,
                                       const QString &callFun, PyObject *pArg,
                                       StdoutWritePointer writer)
{
    return pystd::processPyEvt(modulePath, moduleName, callFun, pArg, writer);
}

PyObject* stdoutWrite(PyObject* self, PyObject* args)
{
    std::size_t written(0);
    Stdout* selfimpl = reinterpret_cast<Stdout*>(self);
    if (selfimpl->write){
        char* data;
        if (!PyArg_ParseTuple(args, "s", &data))
            return 0;

        std::string str(data);
        selfimpl->write(str);
        written = str.size();
    }

    return PyLong_FromSize_t(written);
}

PyObject* stdoutFlush(PyObject* /*self*/, PyObject* /*args*/)
{
    // no-op
    return Py_BuildValue("");
}

PyMethodDef stdout_methods[] =
{
    {"write", stdoutWrite, METH_VARARGS, "sys.stdout.write"},
    {"flush", stdoutFlush, METH_VARARGS, "sys.stdout.flush"},
    {0, 0, 0, 0} // sentinel
};

PyTypeObject stdout_type =
{
    PyVarObject_HEAD_INIT(0, 0)
    "pystd.StdoutType",   /* tp_name */
    sizeof(Stdout),       /* tp_basicsize */
    0,                    /* tp_itemsize */
    0,                    /* tp_dealloc */
    0,                    /* tp_print */
    0,                    /* tp_getattr */
    0,                    /* tp_setattr */
    0,                    /* tp_reserved */
    0,                    /* tp_repr */
    0,                    /* tp_as_number */
    0,                    /* tp_as_sequence */
    0,                    /* tp_as_mapping */
    0,                    /* tp_hash  */
    0,                    /* tp_call */
    0,                    /* tp_str */
    0,                    /* tp_getattro */
    0,                    /* tp_setattro */
    0,                    /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,   /* tp_flags */
    "pystd.Stdout objects", /* tp_doc */
    0,                    /* tp_traverse */
    0,                    /* tp_clear */
    0,                    /* tp_richcompare */
    0,                    /* tp_weaklistoffset */
    0,                    /* tp_iter */
    0,                    /* tp_iternext */
    stdout_methods,       /* tp_methods */
    0,                    /* tp_members */
    0,                    /* tp_getset */
    0,                    /* tp_base */
    0,                    /* tp_dict */
    0,                    /* tp_descr_get */
    0,                    /* tp_descr_set */
    0,                    /* tp_dictoffset */
    0,                    /* tp_init */
    0,                    /* tp_alloc */
    0,                    /* tp_new */
};

PyModuleDef pystd_module =
{
    PyModuleDef_HEAD_INIT,
    "pystd", 0, -1, 0,
};

// Internal state
PyObject* g_stdout;
PyObject* g_stdoutSaved;

PyMODINIT_FUNC PyInit_pystd(void)
{
    g_stdout = 0;
    g_stdoutSaved = 0;

    stdout_type.tp_new = PyType_GenericNew;
    if (PyType_Ready(&stdout_type) < 0){
        return 0;
    }

    PyObject* m = PyModule_Create(&pystd_module);
    if (m){
        Py_INCREF(&stdout_type);
        PyModule_AddObject(m, "Stdout", reinterpret_cast<PyObject*>(&stdout_type));
    }

    return m;
}

void setStdout(StdoutWritePointer write)
{
    if (!g_stdout){
        g_stdoutSaved = PySys_GetObject("stdout"); // borrowed
        g_stdout = stdout_type.tp_new(&stdout_type, 0, 0);
    }

    Stdout* impl = reinterpret_cast<Stdout*>(g_stdout);
    impl->write = write;
    PySys_SetObject("stdout", g_stdout);
}

void resetStdout()
{
    if (g_stdoutSaved){
        PySys_SetObject("stdout", g_stdoutSaved);
    }

    Py_XDECREF(g_stdout);
    g_stdout = 0;
}

PyObject *processPyEvt(const QString &modulePath,
                  const QString &moduleName,
                  const QString &callFun, PyObject *pArg,
                  StdoutWritePointer writer)
{
    pystd::setStdout(writer);

    PyRun_SimpleString("import sys");
    QString setSysPath = QString("sys.path.append('%1')").arg(modulePath);
    PyRun_SimpleString(setSysPath.toStdString().c_str());

    PyObject* pModule = PyImport_ImportModule(moduleName.toStdString().c_str());
    if (!pModule) {
        qDebug() << QString("Can not import module: %1").arg(moduleName);
        return NULL;
    }

    PyObject* pFunhello= PyObject_GetAttrString(pModule, callFun.toStdString().c_str());
    if(!pFunhello){
        qDebug()<< QString("Get function (%1) failed").arg(callFun);
        return NULL;
    }
    PyObject *ret = PyEval_CallObject(pFunhello, pArg);

    pystd::resetStdout();

    return ret;
}

} // namespace pystd
