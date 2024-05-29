#include<node.h>
#include<iostream>
#include<vector>
using namespace std;

template <class Object>
class List
{
public:
  List();
  ~List();

  void push(const Object & obj);
  Object & pop(); /* must be delete'd by caller */
  bool isempty();
  void clear();

  template <class O>
  friend std::ostream & operator<<(std::ostream &stream, const List<O> &list) {
    Element *ptr = list.head;
    while (ptr->next) {
      stream << *ptr->data;
      ptr = ptr->next;
      if (ptr->next) {
	stream << " --> ";
      }
    }
    stream << " --|";
  
    return stream;
  }
  
private:
  struct Element {
    Object *data;
    Element *next;

    Element(const Object & d = Object{ }, Element * n = nullptr)
      : next{n} {
      data = new Object(d);
    }

    Element(Object && d, Element * n = nullptr)
      : data{std::move(d)}, next{n} { }
    
  };

  Element *head;

  void initialize();
};

template <class Object>
List<Object>::List() {
  initialize();
}

template<class Object>
List<Object>::~List() {
  while (!isempty()) {
    Object &popped = pop();
  }
  delete head;
}

template <class Object>
bool List<Object>::isempty() {
  return head->next == nullptr;
}

template <class Object>
void List<Object>::push(const Object & obj) {
  Element *newhead = new Element(obj, head);
  head = newhead;
}

template <typename Object>
Object & List<Object>::pop() {
  if (isempty()) {
    throw std::underflow_error("No element to pop");
  }
  Element *old = head;
  head = old->next;

  Object *rval = old->data;
  delete old;
  
  return *rval;
}

template <class Object>
void List<Object>::initialize() {
  head = new Element;
}


int main(int argc, char** argv) {
  Node<int> node(3);
  cout << "A node: " << node << endl;

  Node<string> node2("Oh hai!");
  cout << "A node: " << node2 << endl;

  vector<Node<int>> v { 1, 2, 3, 4, 5, 6 };

  for ( auto x : v ) {
    cout << x << " ";
  }
  cout << endl;

  for ( auto x : v ) {
    cout << x << " is < 4:  " << (x < Node<int>(4)) << "   ";
    cout << x << " is > 4:  " << (x > Node<int>(4)) << "   ";
    cout << x << " is == 4: " << (x == Node<int>(4)) << "   ";
    cout << x << " is != 4: " << (x != Node<int>(4)) << endl;    
  }
  cout << endl;

  //  vector<Node<string>> s { string("one"), string("two") };
  vector<Node<string>> s { "one", "two", "three" };

  for ( auto x : s ) {
    cout << x << " ";
  }
  cout << endl;

  List<Node<int>> list;  
  for ( auto node : v ) {
    list.push(Node<int>(node));
  }

  cout << list << endl;
  
  while (!list.isempty()) {
    auto val = list.pop();
    cout << val << " ";
  }
  cout << endl;

  cout << "Verifying an empty list can be used once more" << endl;
  vector<Node<int>> z { 10, 20, 30, 40, 50};

  for ( auto node : z ){
    list.push(node);
  }
  cout << list << endl;
  return 0;
}
