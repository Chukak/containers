#ifndef BST_H
#define BST_H

#ifndef NULL
#ifdef __cplusplus
#define NULL nullptr
#endif
#endif

#ifdef __cplusplus
#include <initializer_list>
#include <iterator>
#include <stdexcept>
#include <ostream>

namespace bst_exception {
    class BSTIsEmpty : public std::runtime_error {
    public:
        BSTIsEmpty(const char* message = "The binary search tree is empty.") : 
            std::runtime_error(message) 
        {}
    };
};


using uint = unsigned int;

/*
 * The `bst` class.
 * This class implements the binary search tree.
 * The `bst` class requires operators for elements:
 * 1) `<` - less.
 * 2) `>` - greater.
 */
template<typename E>
class bst {
    
    friend class iterator;
    
    /*
     * Sets the friend function for the overloaded operator `<<`.
     */
    template<typename T>
    friend std::ostream& operator<<(std::ostream& stream, const bst<E>& tree);
    
public:
    
    /*
     * A constructor.
     */
    bst();
    
    /*
     * A constructor, for the style `bst tree = {3, 2, 1}`.
     */
    bst(std::initializer_list<E> lst);
    
    /*
     * A destructor.
     */
    virtual ~bst();
    
    /*
     * The `insert` function.
     * Inserts an element to the tree. If an element less than root,
     * the function inserts it, in the left side of the tree.
     * If an element more than root,
     * the function inserts it, in the right side of the tree.
     * @param element - a constant link to the value.
     */
    void insert(const E& element) noexcept;
    
    /*
     * The `remove` function.
     * Search for an element in the tree. If an element was found,
     * removes it from the tree.
     * If the tree is empty, raises the `BSTIsEmpty` error.
     * @parem - a constant link to the value.
     */
    void remove(const E& element);
    
    /*
     * Returns the minimum element from the tree.
     * If the tree is empty, raises the `BSTIsEmpty` error.
     */
    E min() const;
    
    /*
     * Returns the maximum element from the tree.
     * If the tree is empty, raises the `BSTIsEmpty` error.
     */
    E max() const;
    
    /*
     * Returns the root of the tree.
     * If the tree is empty, raises the `BSTIsEmpty` error.
     */
    E root() const;
    
    /*
     * Returns the number of alements.
     */
    uint count() const noexcept { return count_; }
    
    /*
     * Returns `true` if the tree is empty, otherwise returns `false`.
     */
    bool is_empty() const noexcept { return empty; }
    
    /*
     * The `find` function.
     * Search for an element in the tree. If an element was found,
     * returns `true`, otherwise `false`.
     * If the tree is empty, returns `false`.
     */
    bool find(const E& element) const noexcept;
    
    /*
     * The `clear` function.
     * Clears the tree.
     */
    void clear() noexcept;
    
private:
    
    /*
     * The structure `Node`.
     * Used to representing elements in memory.
     */
    struct Node {
        friend class bst<E>;
        
        friend class iterator;
        
        E data; // a value.
    private:
        Node *right; // a pointer to the right element.
        Node *left; // a pointer to the left element.
        Node *parent; // a pointer to the parent of this element.
        
        /*
         * A constructor.
         */
        Node(const E& e, Node *r, Node *l, Node *p) : 
            data(e), 
            right(r), 
            left(l), 
            parent(p) 
        {}
    };
    
    Node *root_; // a pointer to the root of the tree.
    uint count_; // the numbers of elements.
    bool empty;
    
private:
    
    /*
     * Destroys all elements in the tree.
     */
    void destroy(Node *n) noexcept;
        
public:    
    class iterator;
    
    /*
     * The `iterator` class.
     * Determines the iterator for the sorted list.
     */
    class iterator : public std::iterator<std::forward_iterator_tag, E> {
        /*
         * Sets the friend class.
         */
        friend class bst<E>;
        
    private:
        /*
         * A constructor.
         */
        iterator(Node *node) : current(node)
        {
        }
        
        /*
         * Sets the next element as the current element.
         */
        void increment() noexcept
        {
            // checks the right child.
            if (current->right) {
                current = current->right;
                // find the minimum element in the right child.
                while (current->left) {
                    current = current->left;
                }
            } else {
                Node *parent = current->parent; // parent.
                while (parent && current == parent->right) {
                    current = parent;
                    parent = parent->parent;
                }
                // if all elements is visited.
                if (!parent) {
                    current = parent;
                    return ;
                }
                if (current->right != parent) {
                    current = parent;
                }
            }
        }
            
    public:
        // value type.
        typedef E value_type;
        // iterator category
        typedef std::forward_iterator_tag iterator_category;
        
        /*
         * A constructor.
         */
        iterator() : current(nullptr) {}
        
        /*
         * The prefix operator `++`.
         * Increases the pointer and returns it. 
         */
        iterator& operator++() noexcept
        {
            increment();
            return *this;
        }
        
        /*
         * The postfix operator `++`.
         * Increases the pointer and returns it. 
         */
        iterator& operator++(int j) noexcept
        {
            increment();
            return *this;
        }
        
        /*
         * The operator `*`.
         * Returns a value from the pointer.
         */
        E& operator*() const noexcept
        {
            return current->data;
        }
        
        /*
         * The operator `->`.
         * Returns a pointer to the Node.
         */
        Node* operator->() const noexcept
        {
            return current;
        }
        
        /*
         * The operator `!=`.
         * Compares two iterators. Returns `true` if 
         * iterators are not the same. Otherwise returns `false`.
         */
        bool operator!=(const iterator& rhs) const noexcept
        { 
            return current != rhs.current;
        }
        
        /*
         * The operator `!=`.
         * Returns `true` if the current iterator and `nullptr`
         * are the same. Otherwise returns `false`.
         */
        bool operator!=(std::nullptr_t) const noexcept
        { 
            return current != nullptr;
        }
        
        /*
         * The operator `==`.
         * Compares two iterators. Returns `true` if 
         * iterators are the same. Otherwise returns `false`.
         */
        bool operator==(const iterator& rhs) const noexcept
        { 
            return current == rhs.current;
        }
        
        /*
         * The operator `==`.
         * Returns `true` if the current iterator and `nullptr`
         * are the same. Otherwise returns `false`.
         */
        bool operator==(std::nullptr_t) const noexcept
        { 
            return current == nullptr;
        }
        
    private:
        Node *current; // a pointer to a Node.
        
    };
    
    /*
     * Returns the iterator to the minimum element in the tree.
     */
    iterator begin() const noexcept 
    { 
        Node *temp = root_;
        while (temp && temp->left) {
            temp = temp->left;
        }
        return iterator(temp); 
    }
    
    /*
     * Returns the iterator to the parent of the root of the tree.
     * It is usually `NULL`.
     */
    iterator end() const noexcept 
    { 
        return root_ ? iterator(root_->parent) : iterator(root_); 
    }
    
};

/*
 * A constructor.
 * Creates a new binary search tree.
 */
template<typename E>
bst<E>::bst() :
    root_(NULL),
    count_(0),
    empty(true)
{
}

/*
 * A constructor for the style `bst tree = {3, 5, 1}`.
 */
template<typename E>
bst<E>::bst(std::initializer_list<E> lst) :
    root_(NULL),
    count_(0),
    empty(true)
{
    /*
     * Just copy all the elements.
     */
    for (auto e : lst) {
        insert(e);
    }
}

/*
 * A destructor.
 */
template<typename E>
bst<E>::~bst()
{
    destroy(root_);
    root_ = NULL;
}

/*
 * Destroys all elements in the tree.
 */
template<typename E>
void bst<E>::destroy(Node *n) noexcept
{
    if (n) {
        
        destroy(n->left); // destroys all left elements.
        destroy(n->right); // destroys all right elements.
        delete n;
    }
}

/*
 * The `insert` function.
 * Inserts an element to the tree. If an element less than root,
 * the function inserts it, in the left side of the tree.
 * If an element more than root,
 * the function inserts it, in the right side of the tree.
 */
template<typename E>
void bst<E>::insert(const E& element) noexcept
{
    if (empty) {
        root_ = new Node(element, NULL, NULL, NULL);
        empty = false;
    } else {
        Node *parent = NULL;
        Node *temp = root_;
        bool is_left = false; 
        while (temp) {
            if (element < temp->data) {
                // the left side of the tree.
                parent = temp;
                temp = temp->left;
                is_left = true;
            } else if (element > temp->data) {
                // the right side of the tree.
                parent = temp;
                temp = temp->right;
                is_left = false;
            } else {
                // is element is in the tree.
                return ;
            }
        }
        switch (is_left) {
            case true:
                parent->left = new Node(element, NULL, NULL, parent); 
                break;
            case false:
                parent->right = new Node(element, NULL, NULL, parent);
                break;
        }
    }
    ++count_;
}

/*
 * The `remove` function.
 * Search for an element in the tree. If an element was found,
 * removes it from the tree.
 * If the tree is empty, raises the `BSTIsEmpty` error.
 */
template<typename E>
void bst<E>::remove(const E& element)
{
    if (empty) {
        throw bst_exception::BSTIsEmpty();
    }
    Node *temp = root_; 
    Node *parent = NULL;
    bool is_left = false;
    // search for an element in the tree.
    while(temp) {
        if (temp->data == element) {
            break;
        } else if (temp->data > element) {
            parent = temp;
            temp = temp->left;
            is_left = true;
        } else {
            parent = temp;
            temp = temp->right;
            is_left = false;
        }
    }
    // if an element was not found.
    if (!temp) {
        return ;
    }
    // the function, sets the child.
    auto set_child = [parent, is_left](Node *child) {
        switch (is_left) {
            case true: parent->left = child; break;
            case false: parent->right = child; break;
        }
    };
    // case 1
    // If the right child and the left child is NULL.
    // Just removes it.
    if (!(temp->left) && !(temp->right)) {
        if (!parent) {
            if (temp == root_) {
                root_ = NULL;
            }
        } else {
            set_child(NULL);
        }
        delete temp;
    // case 2
    // If the right child or the left child is NULL.
    // Removes this Node, and replaces it with a child.
    } else if (!(temp->left) || !(temp->right)) {
        Node *child = NULL;
        child = temp->left ? temp->left : temp->right;
        if (!parent) {
            if (temp == root_) {
                root_ = child;
            }
        } else {
            set_child(child);
        }
        delete temp;
    // case 3
    // If the right child and the left child is not NULL.
    // Removes this Node, and replaces it with the left child.
    // And replaces the left child with the right child.
    } else {
        Node *parent_rep_node = temp;
        Node *rep_node = temp->left;
        is_left = true;
        while (rep_node->right) {
            parent_rep_node = rep_node;
            rep_node = rep_node->right;
            is_left = false;
        }
        temp->data = rep_node->data;
        switch (is_left) {
            case true:
                if (!rep_node->right) {
                    temp->left = rep_node->left;
                }
                break;
            case false:
                parent_rep_node->right = rep_node->left;
                break;
        }
         delete rep_node;
    }
    count_--;
    empty = count_ == 0 ? true : false;
}

/*
 * Returns the minimum element from the tree.
 * If the tree is empty, raises the `BSTIsEmpty` error.
 */
template<typename E>
E bst<E>::min() const 
{
    if (empty) {
        throw bst_exception::BSTIsEmpty();
    }
    if (!root_->left) {
        return root_->data;
    }
    Node *temp = root_->left;
    while (temp->left) {
        temp = temp->left;
    }
    return temp->data;
}

/*
 * Returns the maximum element from the tree.
 * If the tree is empty, raises the `BSTIsEmpty` error.
 */
template<typename E>
E bst<E>::max() const 
{
    if (empty) {
        throw bst_exception::BSTIsEmpty();
    }
    if (!root_->right) {
        return root_->data;
    }
    Node *temp = root_->right;
    while (temp->right) {
        temp = temp->right;
    }
    return temp->data;
}

/*
 * Returns the root of the tree.
 * If the tree is empty, raises the `BSTIsEmpty` error.
 */
template<typename E>
E bst<E>::root() const 
{
    if (empty) {
        throw bst_exception::BSTIsEmpty();
    }
    return root_->data;
}

/*
 * The `find` function.
 * Search for an element in the tree. If an element was found,
 * returns `true`, otherwise `false`.
 * If the tree is empty, returns `false`.
 */
template<typename E>
bool bst<E>::find(const E& element) const noexcept
{
    Node *temp = root_;
    while (temp) {
        if (element == temp->data) {
            return true;
        } else if (element < temp->data) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }
    return false;
}

/*
 * Clears the tree.
 */
template<typename E>
void bst<E>::clear() noexcept
{
    if (empty) { 
        return ;
    }
    destroy(root_);
    root_ = NULL;
    count_ = 0;
    empty = true;
}


/*
 * The overloaded `<<` operator for the binary search tree.
 * Prints all elements from the binary search tree in the format: `[1, ...,100]`.
 * Returns ostream.
 */
template<typename T>
std::ostream& operator<<(std::ostream& stream, const bst<T>& tree) 
{
    stream << "[";
    for (auto it = tree.begin(); it != tree.end(); it++) {
        stream << it->data << ", ";
    }
    stream << "\b\b";
    stream << "";
    stream << "]";
    return stream;
}

#endif /* __cplusplus */

#endif /* BST_H */
