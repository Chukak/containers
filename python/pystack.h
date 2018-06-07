#ifndef PYSTACK_H
#define PYSTACK_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include <Python.h>
#include <structmember.h>
#include "../src/stack.h"

typedef struct {
    PyObject_HEAD
    stack *s;
    unsigned int count;
    int empty;
} PyStack;


PyObject *
PyStack_new(PyTypeObject *type, PyObject *args);

void
PyStack_dealloc(PyStack *self);

int
PyStack_init(PyStack *py_s);

PyObject *
PyStack_front(PyObject *self);

PyObject *
PyStack_push(PyObject *self, PyObject *args);

PyObject *
PyStack_pop(PyObject *self);

#ifdef __cplusplus
}
#endif

#endif /* PYSTACK_H */
