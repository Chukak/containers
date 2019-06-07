#include "stack.h"
#include "queue.h"
#include "bst.h"

#include <boost/python.hpp>
using namespace boost::python;



BOOST_PYTHON_MODULE(containers)
{   
#ifdef PY_MODULE_WRAP_METHODS
    // Stack
    class_<Stack<object>, boost::noncopyable>("stack", init<>())
            .def("push", +[](Stack<object> * p, const object& obj) { p->push(obj); }, "Push element into the stack.")
            .def("pop", +[](Stack<object> * p) -> object { return p->pop(); }, "Remove element from the stack.")
            .add_property("count", +[](Stack<object> * p) -> unsigned int { return p->count(); }, "Return number of elements of the stack.")
            .add_property("front", +[](Stack<object> * p) -> object { return p->front(); }, "Return the first element of the stack")
            .add_property("is_empty", +[](Stack<object> * p) -> bool { return p->is_empty(); }, "Return `True` if the stack is empty, otherwise `False`.")
    ;
    // Queue
    class_<Queue<object>, boost::noncopyable>("queue", init<>())
            .def("enqueue", +[](Queue<object> * p, const object& obj) { p->enqueue(obj); }, "Add element into the queue.")
            .def("dequeue", +[](Queue<object> * p) -> object { return p->dequeue(); }, "Remove element from the queue.")
            .add_property("count", +[](Queue<object> * p) -> unsigned int { return p->count(); },"Return number of elements of the queue.")
            .add_property("front", +[](Queue<object> * p) -> object { return p->front(); }, "Return the first element of the queue.")
            .add_property("back", +[](Queue<object> * p) -> object { return p->back();}, "Return the last element of the queue.")
            .add_property("is_empty", +[](Queue<object> * p) -> bool { return p->is_empty();}, "Return `True` if the queue is empty, otherwise `False`.")
            .def("clear", +[](Queue<object> * p) { p->clear(); }, "Clear the queue.")
    ;
    // Binary search tree
    class_<bst<object>, boost::noncopyable>("bst", init<>())
            .def("insert", +[](bst<object> * p, const object& obj) { p->insert(obj); }, "Insert element into the tree.")
            .def("remove", +[](bst<object> * p, const object& obj) { p->remove(obj); }, "Remove element from the tree.")
            .def("find", +[](bst<object> * p, const object& obj) -> bool { return p->find(obj); }, "Search for element in the tree.")
            .def("min", +[](bst<object> * p) -> object { return p->min(); }, "Find and return the minimum element of the tree.")
            .def("max", +[](bst<object> * p) -> object { return p->max(); }, "Find and return the maximum element of the tree.")
            .add_property("root", +[](bst<object> * p) -> object { return p->root(); }, "Return the root of the tree.")
            .add_property("count", +[](bst<object> * p) -> unsigned int { return p->count(); }, "Return number of elements of the tree.")
            .add_property("is_empty", +[](bst<object> * p) -> bool { return p->is_empty(); }, "Return `True` if the tree is empty, otherwise `False`.")
            .def("clear", +[](bst<object> * p) {  p->clear(); }, "Clear the tree.")
            ;
#else
    // Stack
    void (Stack<object>::*Stack_push)(const object&) = &Stack<object>::push;
    class_<Stack<object>, boost::noncopyable>("stack", init<>())
            .def("push", Stack_push, "Push element into the stack.") // &Stack<object>::push
            .def("pop", &Stack<object>::pop, "Remove element from the stack.")
            .add_property("count", &Stack<object>::count, "Return number of elements of the stack.")
            .add_property("front", &Stack<object>::front, "Return the first element of the stack")
            .add_property("is_empty", &Stack<object>::is_empty, "Return `True` if the stack is empty, otherwise `False`.")
            ;
    // Queue
    void (Queue<object>::*Queue_enqueue)(const object&) = &Queue<object>::enqueue;
    class_<Queue<object>, boost::noncopyable>("queue", init<>())
            .def("enqueue", Queue_enqueue, "Add element into the queue.") // &Queue<object>::enqueue
            .def("dequeue", &Queue<object>::dequeue, "Remove element from the queue.")
            .add_property("count", &Queue<object>::count, "Return number of elements of the queue.")
            .add_property("front", &Queue<object>::front, "Return the first element of the queue.")
            .add_property("back", &Queue<object>::back,  "Return the last element of the queue.")
            .add_property("is_empty", &Queue<object>::is_empty, "Return `True` if the queue is empty, otherwise `False`.")
            .def("clear", &Queue<object>::clear, "Clear the queue.")
            ;
    // Binary search tree
    void (bst<object>::*bst_insert)(const object&) = &bst<object>::insert;
    class_<bst<object>, boost::noncopyable>("bst", init<>())
            .def("insert", bst_insert, "Insert element into the tree.") // &bst<object>::insert
            .def("remove", &bst<object>::remove, "Remove element from the tree.")
            .def("find", &bst<object>::find, "Search for element in the tree.")
            .def("min", &bst<object>::min, "Find and return the minimum element of the tree.")
            .def("max", &bst<object>::max, "Find and return the maximum element of the tree.")
            .add_property("root", &bst<object>::root, "Return the root of the tree.")
            .add_property("count", &bst<object>::count, "Return number of elements of the tree.")
            .add_property("is_empty", &bst<object>::is_empty, "Return `True` if the tree is empty, otherwise `False`.")
            .def("clear", &bst<object>::clear, "Clear the tree.")
            ;
#endif
}


