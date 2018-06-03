#ifndef PYSTACK_H
#define PYSTACK_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include <python3.5/Python.h>
#include <python3.5/structmember.h>
#include "../src/stack.h"
#include <stdint.h>

typedef struct {
    PyObject_HEAD
    stack *s;
    uint32_t count;
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