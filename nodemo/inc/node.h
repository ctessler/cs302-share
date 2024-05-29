#ifndef __NODE_H__
#define __NODE_H__

#include<iostream>

template <typename Object>
class Node {
public:
  /* Constructors */
  explicit Node(const Object & init = Object { }) : value{init} { };
  /* rvalue constructor */
  Node(const Object && rhs) : value{rhs} { };
  /*
   * Specific rvalue constructor for const char * because ... C++
   * 
   * This is necessary because only one conversion is allowed, from const char *
   * to string. When invoked, the requested conversion is:
   *
   *    const char * --> string --> Node<string>
   */
  Node(const char* && rhs) : value{rhs} { };

  /* Assignment */
  Node<Object> & operator= (const Object & v) {
    value = v;
    return *this;
  }
  Node<Object> & operator= (const Node<Object> & obj) {
    value = obj.value;
    return *this;
  }

  /* Stream'ify a Node */
  template <typename T>
  friend std::ostream & operator<< (std::ostream &, const Node<T> &);

  /* Comparators */
  template <typename T> friend bool operator<  (const Node<T>&, const Node<T>&);
  template <typename T> friend bool operator>  (const Node<T>&, const Node<T>&);
  template <typename T> friend bool operator<= (const Node<T>&, const Node<T>&);
  template <typename T> friend bool operator>= (const Node<T>&, const Node<T>&);

  /*
   * Equality is defined based on the data value, not on the instance
   * of the Node. Two distinct objects in memory will be equal if
   * their data elements have the same value.
   *
   * Depending on the data structure, this may not be the correct
   * interpretation of equal.
   */
  template <typename T> friend bool operator== (const Node<T>&, const Node<T>&);
  template <typename T> friend bool operator!= (const Node<T>&, const Node<T>&);

private:
  Object value;
};

template <typename T>
std::ostream& operator<<(std::ostream &stream, const Node<T> &node) {
  stream << node.value;
  
  return stream;
}

template <typename T>
bool operator< (const Node<T>& left, const Node<T>& right) {
  return std::tie(left.value) < std::tie(right.value);
}

template <typename T>
bool operator> (const Node<T>& left, const Node<T>& right) {
  return right < left;
}

template <typename T>
bool operator<= (const Node<T>& left, const Node<T>& right) {
    return !(left > right);
}

template <typename T>
bool operator>= (const Node<T>& left, const Node<T>& right) {
    return !(left < right);
}

template <typename T>
bool operator== (const Node<T>& left, const Node<T>& right) {
  return !(left < right) && !(left > right);
}

template <typename T>
bool operator!= (const Node<T>& left, const Node<T>& right) {
  return !(left == right);
}



#endif /* __NODE_H__ */
