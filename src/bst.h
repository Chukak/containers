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

namespace bst_exception {
    class BSTIsEmpty : public std::runtime_error {
    public:
        BSTIsEmpty(const char* message = "The binary search tree is empty.") : 
            std::runtime_error(message) 
        {}
    };
};


using uint = unsigned int;

template<typename E>
class bst {
    
    friend class iterator;
    
public:
    
    /*
     */
    bst();
    
    /*
     */
    bst(const bst<E>& orig);
    
    /*
     */
    bst(std::initializer_list<E> lst);
    
    /*
     */
    virtual ~bst();
    
    /*
     */
    void insert(const E& element) noexcept;
    
    /*
     */
    void remove(const E& element);
    
    /*
     */
    E min() const;
    
    /*
     */
    E max() const;
    
    /*
     */
    E root() const;
    
    /*
     */
    uint count() const noexcept { return count_; }
    
    /*
     */
    bool is_empty() const noexcept { return empty; }
    
    /*
     */
    bool find(const E& element) const noexcept;
    
    /*
     */
    void clear() noexcept;
    
private:
    
    /*
     */
    struct Node {
        friend class bst<E>;
        
        friend class iterator;
        
        E data;
    private:
        Node *right;
        Node *left;
        Node *parent;
        
        /*
         */
        Node(const E& e, Node *r, Node *l, Node *p) : 
            data(e), 
            right(r), 
            left(l), 
            parent(p) 
        {}
    };
    
    Node *root_;
    uint count_;
    bool empty;
    
private:
    
    /*
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
         */
        void increment() noexcept
        {
            if (current->right) {
                current = current->right;
                while (current->left) {
                    current = current->left;
                }
            } else {
                Node *parent = current->parent;
                while (parent && current == parent->right) {
                    current = parent;
                    parent = parent->parent;
                }
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
     */
    iterator end() const noexcept 
    { 
        return root_ ? iterator(root_->parent) : iterator(root_); 
    }
    
};

/*
 */
template<typename E>
bst<E>::bst() :
    root_(NULL),
    count_(0),
    empty(true)
{
}

/*
 */
template<typename E>
bst<E>::bst(const bst<E>& orig) :
    root_(orig.root_),
    count_(orig.count_),
    empty(false)
{
    if (orig.empty) {
        empty = true;
        return ;
    }
}

/*
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
 */
template<typename E>
bst<E>::~bst()
{
    destroy(root_);
}

/*
 */
template<typename E>
void bst<E>::destroy(Node *n) noexcept
{
    if (n) {
        destroy(n->left);
        destroy(n->right);
        delete n;
        n = NULL;
    }
}

/*
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
                parent = temp;
                temp = temp->left;
                is_left = true;
            } else if (element > temp->data) {
                parent = temp;
                temp = temp->right;
                is_left = false;
            } else {
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
    
    if (!temp) {
        return ;
    }
    auto set_child = [parent, is_left](Node *child) {
        switch (is_left) {
            case true: parent->left = child; break;
            case false: parent->right = child; break;
        }
    };
    
    if (!(temp->left) && !(temp->right)) {
        if (!parent) {
            if (temp == root_) {
                root_ = NULL;
            }
        } else {
            set_child(NULL);
        }
        delete temp;
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
 */
template<typename E>
void bst<E>::clear() noexcept
{
    if (empty) { 
        return ;
    }
    destroy(root_);
    delete root_;
    root_ = NULL;
    count_ = 0;
    empty = true;
}


#endif /* __cplusplus */

#endif /* BST_H */

