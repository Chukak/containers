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
#include <memory>

namespace bst_exception {
    class BSTIsEmpty : public std::runtime_error {
    public:
        explicit BSTIsEmpty(const char* message = "The binary search tree is empty.") : 
            std::runtime_error(message) 
        {}
    };
}


using uint = unsigned int;

/*
 * The `bst` class.
 * This class implements the binary search tree.
 * The `bst` class requires operators for elements:
 * 1) `<` - less.
 * 2) `>` - greater.
 */
template<typename E>
class bst
{
    
    friend class iterator;
    
    /*
     * Sets the friend function for the overloaded operator `<<`.
     */
    template<typename T>
    friend std::ostream& operator<<(std::ostream& stream, const bst<E>& tree);
    
public:
    
    /*
     * Constructor.
     */
    bst();
    
    /*
     * Constructor, for the style `bst tree = {3, 2, 1}`.
     */
    bst(std::initializer_list<E> lst);
    
    /*
     * Destructor.
     */
    virtual ~bst();
    
    /*
     * The `insert` function.
     * Inserts an element into the tree. If this element less than the root 
     * of the tree, the function inserts it into the left side of the tree.
     * If this element more than the root of the tree,
     * the function inserts in into the right side of the tree.
     * If this element equal to the root, it doesn`t insert into the tree.
     * @param element - an element.
     */
    void insert(E&& element) noexcept;

    /*
     * The same `insert` function, but for l-value.
     */
    void insert(const E& element) noexcept;
    
    /*
     * The `remove` function.
     * Search for an element in the tree. If an element was found,
     * removes it from the tree.
     * If the tree is empty, throws the `BSTIsEmpty` error.
     * @param - an element.
     */
    void remove(const E& element);
    
    /*
     * Returns the minimum element of the tree.
     * If the tree is empty, throws the `BSTIsEmpty` error.
     */
    E min() const;
    
    /*
     * Returns the maximum element of the tree.
     * If the tree is empty, throws the `BSTIsEmpty` error.
     */
    E max() const;
    
    /*
     * Returns the root of the tree.
     * If the tree is empty, throws the `BSTIsEmpty` error.
     */
    E root() const;
    
    /*
     * Returns the number of elements.
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
        std::shared_ptr<Node> right; // a pointer to the right element.
        std::shared_ptr<Node> left; // a pointer to the left element.
        std::shared_ptr<Node> parent; // a pointer to the parent of this element.
        
        /*
         * Сonstructor.
         */
        Node(E&& e, std::shared_ptr<Node> r,
            std::shared_ptr<Node> l, std::shared_ptr<Node> p) :
            data(e), 
            right(r), 
            left(l), 
            parent(p) 
        {}
    };
    
    using sptr = std::shared_ptr<Node>;
    
    /*
     * Pseudonym for code: `std::make_shared<Node>(Node(...))`.
     */
    template<typename... Args>
    auto make_sptr(Args&&... args) 
    -> decltype(std::make_shared<Node>(std::forward<Args>(args)...)) 
    {
        return std::make_shared<Node>(std::forward<Args>(args)...);
    }
    
    sptr root_; // a pointer to the root of the tree.
    uint count_; // the numbers of elements.
    bool empty;
    
private:
    
    /*
     * Destroys all the elements in the tree.
     */
    void destroy(sptr n) noexcept;
        
public:    
    class iterator;
    
    /*
     * The `iterator` class.
     * Implements the iterator for the tree.
     * The iterator is `forward_iterator`.
     */
    class iterator : public std::iterator<std::forward_iterator_tag, E> {
        
        friend class bst<E>;
        
    private:
        /*
         * Constructor.
         */
        explicit iterator(sptr node) : current(node)
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
                // find the minimum element of the right child.
                while (current->left) {
                    current = current->left;
                }
            } else {
                sptr parent = current->parent; // parent.
                while (parent && current == parent->right) {
                    current = parent;
                    parent = parent->parent;
                }
                // if all the elements is visited.
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
         * Constructor.
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
        iterator operator++([[maybe_unused]] int j) noexcept
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
            return current.get();
        }
        
        /*
         * The operator `!=`.
         * Compares two iterators. Returns `true` if 
         * iterators aren`t the same. Otherwise returns `false`.
         */
        bool operator!=(const iterator& rhs) const noexcept
        { 
            return current != rhs.current;
        }
        
        /*
         * The operator `!=`.
         * Returns `true` if the current iterator and `nullptr`
         * aren`t the same. Otherwise returns `false`.
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
        sptr current; // a pointer to a Node.
        
    };
    
    /*
     * Returns the iterator to the minimum element of the tree.
     */ 
    iterator begin() const noexcept 
    { 
        sptr temp = root_;
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
 * Constructor.
 * Creates a new binary search tree.
 */
template<typename E>
bst<E>::bst() :
    root_(sptr(NULL)),
    count_(0),
    empty(true)
{
}

/*
 * constructor for the style `bst tree = {3, 5, 1}`.
 */
template<typename E>
bst<E>::bst(std::initializer_list<E> lst) :
    root_(sptr(NULL)),
    count_(0),
    empty(true)
{
    /*
     * Just copy all the elements.
     */
    for (auto e : lst) {
        insert(std::move(e));
    }
}

/*
 * Destructor.
 */
template<typename E>
bst<E>::~bst()
{
    destroy(root_);
    root_ = sptr(NULL);
}

/*
 * Destroys all the elements in the tree.
 */
template<typename E>
void bst<E>::destroy(sptr n) noexcept
{
    if (n) {
        destroy(n->left); // destroys all left elements.
        destroy(n->right); // destroys all right elements.
        n.reset();
    }
}

/*
 * The `insert` function.
 * Inserts an element into the tree. If this element less than the root,
 * the function inserts it into the left side of the tree.
 * If an element more than the root,
 * the function inserts it into the right side of the tree.
 */ 
template<typename E>
void bst<E>::insert(E&& element) noexcept
{
    if (empty) {
        // this code is `std::make_shared<Node>(Node(...))`.
        root_ = make_sptr(Node(std::move(element), NULL, NULL, NULL));
        empty = false;
    } else {
        sptr parent = sptr(NULL);
        sptr temp = root_;
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

        if (is_left) {
            parent->left = make_sptr(Node(std::move(element), NULL, NULL, parent));
        } else {
            parent->right = make_sptr(Node(std::move(element), NULL, NULL, parent));
        }
    }
    ++count_;
} 

template<typename E>
void bst<E>::insert(const E& element) noexcept
{
    insert(std::move(std::remove_const_t<E>(element)));
}

/*
 * The `remove` function.
 * Search for an element in the tree. If an element was found,
 * removes it from the tree.
 * If the tree is empty, throws the `BSTIsEmpty` error.
 */ 
template<typename E>
void bst<E>::remove(const E& element)
{
    if (empty) {
        throw bst_exception::BSTIsEmpty();
    }
    sptr temp = root_; 
    sptr parent = sptr(NULL);
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
    // the function, sets the parent.
    constexpr auto set_parent = [](sptr child, sptr new_parent) {
        if (child) {
            child->parent = new_parent;
        }
    };
    // the function, sets the child.
    auto set_child = [&parent, &is_left, &set_parent](sptr child) {
        if (is_left) {
            parent->left = child;
            set_parent(child, parent->left);
        } else {
            parent->right = child;
            set_parent(child, parent->right);
        }
    };
    // case 1.
    // If the right child and the left child is NULL.
    // Just removes it.
    if (!(temp->left) && !(temp->right)) {
        if (!parent) {
            if (temp == root_) {
                root_ = sptr(NULL);
            }
        } else {
            set_child(sptr(NULL));
        }
        temp.reset();
    // case 2.
    // If the right child or the left child is NULL.
    // Removes this node, and replaces it with the right or left child.
    } else if (!(temp->left) || !(temp->right)) {
        sptr child = temp->left ? temp->left : temp->right;
        if (!parent) {
            if (temp == root_) {
                root_ = child;
            }
        } else {
            set_child(child);
        }
        temp.reset();
    // case 3.
    // If the right child and the left child is not NULL.
    // Removes this Node, and replaces it with the left child.
    // And replaces the left child with the right child.
    } else {
        sptr parent_rep_node = temp;
        sptr rep_node = temp->left;
        is_left = true;
        while (rep_node->right) {
            parent_rep_node = rep_node;
            rep_node = rep_node->right;
            is_left = false;
        }
        temp->data = rep_node->data;
        if (is_left) {
            if (!rep_node->right) {
                temp->left = rep_node->left;
                set_parent(rep_node->left, temp->left);
            }
        } else {
            parent_rep_node->right = rep_node->left;
            set_parent(rep_node->left, parent_rep_node->right);
        }
        rep_node.reset();
    }
    count_--;
    empty = count_ == 0 ? true : false;
} 

/*
 * Returns the minimum element of the tree.
 * If the tree is empty, throws the `BSTIsEmpty` error.
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
    sptr temp = root_->left;
    while (temp->left) {
        temp = temp->left;
    }
    return temp->data;
} 

/*
 * Returns the maximum element of the tree.
 * If the tree is empty, throws the `BSTIsEmpty` error.
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
    sptr temp = root_->right;
    while (temp->right) {
        temp = temp->right;
    }
    return temp->data;
} 

/*
 * Returns the root of the tree.
 * If the tree is empty, throws the `BSTIsEmpty` error.
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
    sptr temp = root_;
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
    root_ = sptr(NULL);
    count_ = 0;
    empty = true;
}
 

/*
 * The overloaded `<<` operator for the binary search tree.
 * Prints all elements from the binary search tree 
 * in the format: `[1, ...,100]`.
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
