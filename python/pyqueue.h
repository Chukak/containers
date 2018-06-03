#ifndef PYQUEUE_H
#define PYQUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <Python.h>
#include <structmember.h>
#include "../src/queue.h"
#include <stdint.h>
    
typedef struct {
    PyObject_HEAD
    queue *q;
    uint32_t count;
    int empty;
} PyQueue;


PyObject *
PyQueue_new(PyTypeObject *type, PyObject *args);

void
PyQueue_dealloc(PyQueue *self);

int
PyQueue_init(PyQueue *py_q);

PyObject *
PyQueue_front(PyObject *self);

PyObject *
PyQueue_back(PyObject *self);

PyObject *
PyQueue_enqueue(PyObject *self, PyObject *args);

PyObject *
PyQueue_dequeue(PyObject *self);


#ifdef __cplusplus
}
#endif

#endif /* PYQUEUE_H */
