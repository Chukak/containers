#include <Python.h>
#include <structmember.h>
#include "pyqueue.h"
#include "pystack.h"

#if PY_MAJOR_VERSION >= 3
#define INIT_ERROR return NULL
#else
#define INIT_ERROR return
#endif


struct module_state {
    PyObject *error;
};

static PyMemberDef PyQueue_members[] = {
    {
        "count",
        T_INT, 
        offsetof(PyQueue, count), 
        READONLY, 
        "Numbers of elements in the queue."
    },
    {
        "empty", 
        T_INT, 
        offsetof(PyQueue, empty), 
        READONLY, 
        "`True` if the queue is empty."
    },
    {NULL}
};

static PyMethodDef PyQueue_methods[] = {
    {
        "front", 
        (PyCFunction)PyQueue_front, 
        METH_NOARGS, 
        "Returns a front element in the queue."
    },
    {
        "back", 
        (PyCFunction)PyQueue_back, 
        METH_NOARGS, 
        "Returns a back element in the queue."
    },
    {
        "enqueue", 
        (PyCFunction)PyQueue_enqueue, 
        METH_O,
        "Inserts a value at the end of the queue."
    },
    {
        "dequeue", 
        (PyCFunction)PyQueue_dequeue, 
        METH_NOARGS, 
        "Removes a value from the start of the queue."
    }, 
    {NULL}
};


static PyTypeObject PyQueue_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "containers.queue",                                 /* tp_name */
    sizeof(PyQueue),                                    /* tp_basicsize */
    0,                                                  /* itemsize */
    (destructor)PyQueue_dealloc,                        /* tp_dealloc */
    (printfunc)0,                                       /* tp_print */
    (getattrfunc)0,                                     /* tp_getattr */
    (setattrfunc)0,                                     /* tp_setattr */
#if PY_VERSION_HEX >= 0x03050000
    (PyAsyncMethods *)0,                                /* tp_as_async */
#elif PY_VERSION_HEX >= 0x03000000
    (void *)0,                                          /* tp_reserved */
#else
    0,                                                  /* tp_compare */
#endif
    (reprfunc)0,                                        /* tp_repr */
    (PyNumberMethods *)0,                               /* tp_as_number */
    (PySequenceMethods *)0,                             /* tp_as_sequence */
    (PyMappingMethods *)0,                              /* tp_as_mapping */
    (hashfunc)0,                                        /* tp_hash */
    (ternaryfunc)0,                                     /* tp_call */
    (reprfunc)0,                                        /* tp_str */
    (getattrofunc)0,                                    /* tp_getattro */
    (setattrofunc)0,                                    /* tp_setattro */
    (PyBufferProcs *)0,                                 /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE,             /* tp_flags */
    0,                                                  /* tp_doc */
    (traverseproc)0,                                    /* tp_traverse */
    (inquiry)0,                                         /* tp_clear */
    (richcmpfunc)0,                                     /* tp_richcompare */
    0,                                                  /* tp_weaklistoffset */
    (getiterfunc)0,                                     /* tp_iter */
    (iternextfunc)0,                                    /* tp_iternext */
    (struct PyMethodDef *)PyQueue_methods,              /* tp_methods */
    (struct PyMemberDef *)PyQueue_members,              /* tp_members */
    0,                                                  /* tp_getset */
    0,                                                  /* tp_base */
    0,                                                  /* tp_dict */
    (descrgetfunc)0,                                    /* tp_descr_get */
    (descrsetfunc)0,                                    /* tp_descr_set */
    0,                                                  /* tp_dictoffset */
    (initproc)PyQueue_init,                             /* tp_init */
    0,                                                  /* tp_alloc */
    (newfunc)PyQueue_new,                               /* tp_new */
    (freefunc)0,                                        /* tp_free */
    (inquiry)0,                                         /* tb_is_gc */
    0,                                                  /* tp_bases */
    0,                                                  /* tp_mro */
    0,                                                  /* tp_cache */
    0,                                                  /* tp_subclasses */
    0,                                                  /* tp_weaklist */
    (destructor)0                                       /* tp_del */
};

static PyMemberDef PyStack_members[] = {
    {
        "count",
        T_INT, 
        offsetof(PyStack, count), 
        READONLY, 
        "Numbers of elements in the stack."
    },
    {
        "empty", 
        T_INT, 
        offsetof(PyStack, empty), 
        READONLY, 
        "`True` if the stack is empty."
    },
    {NULL}
};

static PyMethodDef PyStack_methods[] = {
    {
        "front", 
        (PyCFunction)PyStack_front, 
        METH_NOARGS, 
        "Returns a front element in the stack."
    },
    {
        "push", 
        (PyCFunction)PyStack_push, 
        METH_O,
        "Inserts a value at the end of the stack."
    },
    {
        "pop", 
        (PyCFunction)PyStack_pop, 
        METH_NOARGS, 
        "Removes a value from the start of the stack."
    },
    {NULL}
};


static PyTypeObject PyStack_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "containers.stack",                                 /* tp_name */
    sizeof(PyStack),                                    /* tp_basicsize */
    0,                                                  /* itemsize */
    (destructor)PyStack_dealloc,                        /* tp_dealloc */
    (printfunc)0,                                       /* tp_print */
    (getattrfunc)0,                                     /* tp_getattr */
    (setattrfunc)0,                                     /* tp_setattr */
#if PY_VERSION_HEX >= 0x03050000
    (PyAsyncMethods *)0,                                /* tp_as_async */
#elif PY_VERSION_HEX >= 0x03000000
    (void *)0,                                          /* tp_reserved */
#else
    0,                                                  /* tp_compare */
#endif
    (reprfunc)0,                                        /* tp_repr */
    (PyNumberMethods *)0,                               /* tp_as_number */
    (PySequenceMethods *)0,                             /* tp_as_sequence */
    (PyMappingMethods *)0,                              /* tp_as_mapping */
    (hashfunc)0,                                        /* tp_hash */
    (ternaryfunc)0,                                     /* tp_call */
    (reprfunc)0,                                        /* tp_str */
    (getattrofunc)0,                                    /* tp_getattro */
    (setattrofunc)0,                                    /* tp_setattro */
    (PyBufferProcs *)0,                                 /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE,             /* tp_flags */
    0,                                                  /* tp_doc */
    (traverseproc)0,                                    /* tp_traverse */
    (inquiry)0,                                         /* tp_clear */
    (richcmpfunc)0,                                     /* tp_richcompare */
    0,                                                  /* tp_weaklistoffset */
    (getiterfunc)0,                                     /* tp_iter */
    (iternextfunc)0,                                    /* tp_iternext */
    (struct PyMethodDef *)PyStack_methods,              /* tp_methods */
    (struct PyMemberDef *)PyStack_members,              /* tp_members */
    0,                                                  /* tp_getset */
    0,                                                  /* tp_base */
    0,                                                  /* tp_dict */
    (descrgetfunc)0,                                    /* tp_descr_get */
    (descrsetfunc)0,                                    /* tp_descr_set */
    0,                                                  /* tp_dictoffset */
    (initproc)PyStack_init,                             /* tp_init */
    0,                                                  /* tp_alloc */
    (newfunc)PyStack_new,                               /* tp_new */
    (freefunc)0,                                        /* tp_free */
    (inquiry)0,                                         /* tb_is_gc */
    0,                                                  /* tp_bases */
    0,                                                  /* tp_mro */
    0,                                                  /* tp_cache */
    0,                                                  /* tp_subclasses */
    0,                                                  /* tp_weaklist */
    (destructor)0                                       /* tp_del */
};

static PyMethodDef containers_methods[] = {
    {NULL}
};

#if PY_MAJOR_VERSION >= 3
static PyModuleDef py_module = {
    PyModuleDef_HEAD_INIT,
    "containers",
    NULL,
    sizeof(struct module_state),
    containers_methods,
    NULL
};


PyMODINIT_FUNC PyInit_containers(void)
#else 
PyMODINIT_FUNC initcontainers(void)
#endif
{
#if PY_MAJOR_VERSION >= 3
    PyObject *m = PyModule_Create(&py_module);
#else
    PyObject *m = Py_InitModule("containers", containers_methods);
#endif
    if (!m) {
        INIT_ERROR;
    }
    if (PyType_Ready(&PyQueue_type) > 0) {
        INIT_ERROR;
    }
    PyObject *queue_class = (PyObject *)&PyQueue_type;
    if (!queue_class) {
        INIT_ERROR;
    } 
    Py_INCREF(queue_class);
    if (PyModule_AddObject(m, "queue", queue_class) < 0) {
        INIT_ERROR;
    }
    if (PyType_Ready(&PyStack_type) > 0) {
        INIT_ERROR;
    }
    PyObject *stack_class = (PyObject *)&PyStack_type;
    if (!stack_class) {
        INIT_ERROR;
    } 
    Py_INCREF(stack_class);
    if (PyModule_AddObject(m, "stack", stack_class) < 0) {
        INIT_ERROR;
    } 
#if PY_MAJOR_VERSION >= 3
    return m;
#endif
}
  