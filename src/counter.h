#ifndef COUNTER_H
#define COUNTER_H

#ifdef __cplusplus
#ifndef NULL
#define NULL nullptr
#endif
#endif

#ifdef __cplusplus
#include <initializer_list>
#include <map>
#include <vector>
#include <set>
#include <ostream>
#include <utility>
#include <algorithm>
#include <iterator>
#include <functional>
#include <type_traits>
#include <iostream>


using uint = unsigned int;


/*
 */
template<typename T>
class Counter {

public:
    
    /*
     */
    typedef std::vector<std::pair<T, uint>> vector_t;
    
    /*
     */
    typedef std::map<T, uint> map_t;
    
    /*
     */
    typedef std::pair<T, uint> pair_t;
    
    /*
     */
    template<typename IteratorBegin, typename IteratorEnd>
    explicit Counter(IteratorBegin _begin, IteratorEnd _end);
    
    /*
     */
    virtual ~Counter();
    
    /*
     */
    std::vector<std::pair<T, uint>> most_common(int n = -1);
    
    /*
     */
    template<typename Array>
    void most_common(Array& list, int n = -1);
    
    /*
     */
    template<typename IteratorBegin, typename IteratorEnd>
    void update(IteratorBegin begin, IteratorEnd end);
    
    /*
     */
    template<typename IteratorBegin, typename IteratorEnd>
    static std::map<T, uint> map(IteratorBegin _begin, IteratorEnd _end);
    
    /*
     */
    uint size() const noexcept
    {
        return _elements.size();
    }
    
private:
    
    using vc_it = typename std::vector<std::pair<T, uint>>::const_iterator;
    
    /*
     */
    auto count(int& n) -> std::pair<vc_it, vc_it>;
    
    /*
     */
    void update();
    
    std::map<T, uint> _elements; //
    std::vector<std::pair<T, uint>> _current; //
    
public:
    class iterator;
    
    /*
     */
    class iterator : public std::iterator<std::forward_iterator_tag, T> {
        
        friend class Counter<T>;
        
    private:
        /*
         */
        explicit iterator(vc_it it) : _begin(it) 
        {}
        
    public:
        // value type.
        typedef T value_type;
        // iterator category
        typedef std::forward_iterator_tag iterator_category;
        
        /*
         */
        iterator() : _begin(NULL) {}
        
        /*
         * The prefix operator `++`.
         * Increases the pointer and returns it. 
         */
        iterator& operator++() noexcept
        {
            _begin++;
            return *this;
        }
        
        /*
         * The postfix operator `++`.
         * Increases the pointer and returns it. 
         */
        iterator operator++(int j) noexcept
        {
            _begin++;
            return *this;
        }
        
        /*
         * The operator `*`.
         * Returns a value from the pair.
         */
        T operator*() const noexcept
        {
            return (*_begin).first;
        }
        
        /*
         * The operator `->`.
         * Returns a pointer to the pair.
         */
        const std::pair<T, uint>* operator->() const noexcept
        {
            return &(*_begin);
        }
        
        /*
         * The operator `!=`.
         * Compares two iterators. Returns `true` if 
         * iterators aren`t the same. Otherwise returns `false`.
         */
        bool operator!=(const iterator& rhs) const noexcept
        { 
            return _begin != rhs._begin;
        }
        
        /*
         * The operator `!=`.
         * Returns `true` if the current iterator and `nullptr`
         * aren`t the same. Otherwise returns `false`.
         */
        bool operator!=(std::nullptr_t) const noexcept
        { 
            return _begin != nullptr;
        }
        
        /*
         * The operator `==`.
         * Compares two iterators. Returns `true` if 
         * iterators are the same. Otherwise returns `false`.
         */
        bool operator==(const iterator& rhs) const noexcept
        { 
            return _begin == rhs._begin;
        }
        
        /*
         * The operator `==`.
         * Returns `true` if the current iterator and `nullptr`
         * are the same. Otherwise returns `false`.
         */
        bool operator==(std::nullptr_t) const noexcept
        { 
            return _begin == nullptr;
        }
        
    private:
        vc_it _begin; //
    
    };
    
    /*
     */
    template<template <class ... > class Array,
            typename IteratorBegin, 
            typename IteratorEnd>
    static Array<std::pair<T, uint>> count(IteratorBegin begin, IteratorEnd end);
    
    /*
     */
    iterator begin() noexcept
    {
        update();
        return iterator(_current.begin());
    }
    
    /*
     */
    iterator end() const noexcept
    {
        return iterator(_current.end());
    }
    
};

/*
 */
template<typename T>
template<typename IteratorBegin, typename IteratorEnd>
Counter<T>::Counter(IteratorBegin _begin, IteratorEnd _end) :
    _elements(),
    _current()
{
    for (auto it = _begin; it != _end; it++) {
        _elements[*it]++;
    }
}

/*
 */
template<typename T>
Counter<T>::~Counter()
{
}

/*
 */
template<typename T>
template<typename IteratorBegin, typename IteratorEnd>
std::map<T, uint> Counter<T>::map(IteratorBegin _begin, IteratorEnd _end)
{
    std::map<T, uint> result;
    for (auto it = _begin; it != _end; it++) {
        result[*it]++;
    }
    return result;
}

template<typename T>
template<template <class ... > class Array,
        typename IteratorBegin, 
        typename IteratorEnd>
Array<std::pair<T, uint>> Counter<T>::count(IteratorBegin _begin, IteratorEnd _end)
{
    std::map<T, uint> map;
    for (auto it = _begin; it != _end; it++) {
        map[*it]++;
    }
    std::vector<std::pair<T, uint>> vec;
    
    std::copy(map.begin(), map.end(), std::back_inserter(vec)); 
    std::sort(vec.begin(), vec.end(), 
            [](const std::pair<T, uint>& a, const std::pair<T, uint>& b) -> bool { 
                return a.second > b.second; 
            });
            
    Array<std::pair<T, uint>> result;
    
    std::transform(vec.begin(), vec.end(), std::inserter(result, std::begin(result)),
            [](std::pair<T, uint> p) -> std::pair<T, uint> {
               return p; 
            });
    
    return result;
}
    
/*
 */
template<typename T>
auto Counter<T>::count(int& n) -> std::pair<Counter<T>::vc_it, Counter<T>::vc_it>
{
    update();
    vc_it end = _current.end();
    if (n != -1 && static_cast<uint>(n) <= _elements.size()) {
        end = _current.begin() + n;
    }
    return std::pair<vc_it, vc_it>(_current.begin(), end);
}

/*
 */
template<typename T>
void Counter<T>::update()
{
    _current.clear();
    std::copy(_elements.begin(), _elements.end(), 
            std::back_inserter(_current)); 
    std::sort(_current.begin(), _current.end(), 
            [](std::pair<T, uint>& a, std::pair<T, uint>& b) -> bool { 
                return a.second > b.second; 
            });
}

/*
 */
template<typename T>
std::vector<std::pair<T, uint>> Counter<T>::most_common(int n)
{
    auto iterators = count(n);
    return std::vector<std::pair<T, uint>>(iterators.first, iterators.second);
}

/*
 */
template<typename T>
template<typename Array>
void Counter<T>::most_common(Array& list, int n)
{
    auto iterators = count(n);
    std::transform(iterators.first, iterators.second,
            std::inserter(list, std::begin(list)),
            [](const std::pair<T, uint>& p) -> T {
               return p.first; 
            });
}

/*
 */
template<typename T>
template<typename IteratorBegin, typename IteratorEnd>
void Counter<T>::update(IteratorBegin _begin, IteratorEnd _end)
{
    for (auto it = _begin; it != _end; it++) {
        _elements[*it]++;
    }
}


#endif

#endif /* COUNTER_H */
