#include "stack.h"
#include "queue.h"
#include "bst.h"

#include <boost/python.hpp>
using namespace boost::python;


BOOST_PYTHON_MODULE(containers)
{
    // Stack
    class_<Stack<object>, boost::noncopyable>("stack", init<>())
            .def("push",
                 +[](Stack<object> * p, const object& obj)
    {
        p->push(std::move(std::remove_const_t<object>(obj)));
    }, "Push element into the stack.")
            .def("pop", &Stack<object>::pop, "Remove element from the stack.")
            .def_readonly("count", &Stack<object>::count,
                          "Return number of elements of the stack.")
            .def_readonly("front", &Stack<object>::front,
                          "Return the first element of the stack")
            .def_readonly("is_empty", &Stack<object>::is_empty,
                          "Return `True` if the stack is empty, otherwise `False`.")
            ;
    // Queue
    class_<Queue<object>, boost::noncopyable>("queue", init<>())
            .def("enqueue",
                 +[](Queue<object> * p, const object& obj)
    {
        p->enqueue(std::move(std::remove_const_t<object>(obj)));
    }, "Add element into the queue.")
            .def("dequeue", &Queue<object>::dequeue, "Remove element from the queue.")
            .def_readonly("count", &Queue<object>::count,
                          "Return number of elements of the queue.")
            .def_readonly("front", &Queue<object>::front,
                          "Return the first element of the queue.")
            .def_readonly("back", &Queue<object>::back,
                          "Return the last element of the queue.")
            .def_readonly("is_empty", &Queue<object>::is_empty,
                          "Return `True` if the queue is empty, otherwise `False`.")
            .def("clear", &Queue<object>::clear, "Clear the queue.")
            ;
    // Binary search tree
    class_<bst<object>, boost::noncopyable>("bst", init<>())
            .def("insert",
                 +[](bst<object> * p, const object& obj)
    {
        p->insert(std::move(std::remove_const_t<object>(obj)));
    }, "Insert element into the tree.")
            .def("remove", &bst<object>::remove,
                 "Remove element from the tree.")
            .def("find", &bst<object>::find,
                 "Search for element in the tree.")
            .def_readonly("min", &bst<object>::min,
                          "Return the minimum element of the tree.")
            .def_readonly("max", &bst<object>::max,
                          "Return the maximum element of the tree.")
            .def_readonly("root", &bst<object>::root,
                          "Return the root of the tree.")
            .def_readonly("count", &bst<object>::count,
                          "Return number of elements of the tree.")
            .def_readonly("is_empty", &bst<object>::is_empty,
                          "Return `True` if the tree is empty, otherwise `False`.")
            .def("clear", &bst<object>::clear, "Clear the tree.")
            ;
}
