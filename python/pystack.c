#include "pystack.h"

PyObject *
PyStack_new(PyTypeObject *type, PyObject *args) 
{
    PyStack *py_s = (PyStack *)type->tp_alloc(type, 0);
    if (!py_s) {
        PyErr_SetString(PyExc_RuntimeError, "Can not allocate memory for an object.");
        PyErr_Print();
        return NULL;
    }
    return (PyObject *)py_s;
}

void
PyStack_dealloc(PyStack *self)
{
    s_delete_stack(self->s);
#if PY_MAJOR_VERSION >= 3
    self->ob_base.ob_type->tp_free((PyObject *)self);
#else
    self->ob_type->tp_free((PyObject *)self);
#endif
}

int
PyStack_init(PyStack *py_s)
{
    stack *s = s_create_stack();
    if (!s) {
        PyErr_SetString(PyExc_RuntimeError, "The pointer on the stack is NULL.");
        PyErr_Print();
        return -1;
    }
    py_s->s = s;
    py_s->count = 0;
    py_s->empty = 1;
    return 0;
}

PyObject *
PyStack_front(PyObject *self)
{
    PyStack *py_s = (PyStack *)self;
    if (!py_s) {
        PyErr_SetString(PyExc_RuntimeError, "The pointer on the stack is NULL.");
        PyErr_Print();
        return NULL;
    }
    void *p = s_front(py_s->s);
    if (!p) {
        Py_RETURN_NONE;
    }
    PyObject *front = (*(PyObject **)p); 
    return Py_BuildValue("O", front);
}

PyObject *
PyStack_push(PyObject *self, PyObject *args)
{
    PyObject *o = NULL;
    if (!PyArg_Parse(args, "O", &o)) {
        PyErr_SetString(PyExc_TypeError, "Missing 1 positional argument `value`..");
        PyErr_Print();
        return NULL;
    }
    PyStack *py_s = (PyStack *)self;
    if (!py_s) {
        PyErr_SetString(PyExc_RuntimeError, "The pointer on the stack is NULL.");
        PyErr_Print();
        return NULL;
    }
    Py_INCREF(o);
    if (!o) {
        return NULL;
    }
    s_push(py_s->s, &o);
    py_s->count = py_s->s->count;
    py_s->empty = py_s->s->empty;
    return Py_BuildValue("N", PyBool_FromLong(1));
}

PyObject *
PyStack_pop(PyObject *self)
{
    PyStack *py_s = (PyStack *)self;
    if (!py_s) {
        PyErr_SetString(PyExc_RuntimeError, "The pointer on the stack is NULL.");
        PyErr_Print();
        return NULL;
    }
    void *p = s_pop(py_s->s);
    if (!p) {
        Py_RETURN_NONE;
    }
    PyObject *element = (*(PyObject **)p);
    py_s->count = py_s->s->count;
    py_s->empty = py_s->s->empty;
    return Py_BuildValue("O", element);
}
