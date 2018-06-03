#include "pyqueue.h"

PyObject *
PyQueue_new(PyTypeObject *type, PyObject *args) 
{
    PyQueue *py_q = (PyQueue *)type->tp_alloc(type, 0);
    if (!py_q) {
        PyErr_SetString(PyExc_RuntimeError, "Can not allocate memory for an object.");
        PyErr_Print();
        return NULL;
    }
    return (PyObject *)py_q;
}

void
PyQueue_dealloc(PyQueue *self)
{
    q_delete_queue(self->q);
#if PY_MAJOR_VERSION >= 3
    self->ob_base.ob_type->tp_free((PyObject *)self);
#else
    self->ob_type->tp_free((PyObject *)self);
#endif
}

int
PyQueue_init(PyQueue *py_q)
{
    queue *q = q_create_queue();
    if (!q) {
        PyErr_SetString(PyExc_RuntimeError, "The pointer on the queue is NULL.");
        PyErr_Print();
        return -1;
    }
    py_q->q = q;
    py_q->count = 0;
    py_q->empty = 1;
    return 0;
}

PyObject *
PyQueue_front(PyObject *self)
{
    PyQueue *py_q = (PyQueue *)self;
    if (!py_q) {
        PyErr_SetString(PyExc_RuntimeError, "The pointer on the queue is NULL.");
        PyErr_Print();
        return NULL;
    }
    void *p = q_front(py_q->q);
    if (!p) {
        Py_RETURN_NONE;
    }
    PyObject *front = (*(PyObject **)p); 
    return Py_BuildValue("O", front);
}

PyObject *
PyQueue_back(PyObject *self)
{
    PyQueue *py_q = (PyQueue *)self;
    if (!py_q) {
        PyErr_SetString(PyExc_RuntimeError, "The pointer on the queue is NULL.");
        PyErr_Print();
        return NULL;
    }
    void *p = q_back(py_q->q);
    if (!p) {
        Py_RETURN_NONE;
    }
    PyObject *back = (*(PyObject **)p);
    return Py_BuildValue("O", back);
}

PyObject *
PyQueue_enqueue(PyObject *self, PyObject *args)
{
    PyObject *o = NULL;
    if (!PyArg_Parse(args, "O", &o)) {
        PyErr_SetString(PyExc_TypeError, "Missing 1 positional argument `value`..");
        PyErr_Print();
        return NULL;
    }
    PyQueue *py_q = (PyQueue *)self;
    if (!py_q) {
        PyErr_SetString(PyExc_RuntimeError, "The pointer on the queue is NULL.");
        PyErr_Print();
        return NULL;
    }
    Py_INCREF(o);
    if (!o) {
        return NULL;
    }
    q_enqueue(py_q->q, &o);
    py_q->count = py_q->q->count;
    py_q->empty = py_q->q->empty;
    return Py_BuildValue("N", PyBool_FromLong(1));
}

PyObject *
PyQueue_dequeue(PyObject *self)
{
    PyQueue *py_q = (PyQueue *)self;
    if (!py_q) {
        PyErr_SetString(PyExc_RuntimeError, "The pointer on the queue is NULL.");
        PyErr_Print();
        return NULL;
    }
    void *p = q_dequeue(py_q->q);
    if (!p) {
        Py_RETURN_NONE;
    }
    PyObject *element = (*(PyObject **)p);
    py_q->count = py_q->q->count;
    py_q->empty = py_q->q->empty;
    return Py_BuildValue("O", element);
}
