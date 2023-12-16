#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

    List()
    {
        first = nullptr;
        last = nullptr;
        numElements = 0;
    }

    List(const List& other) : List()
    {
        copy_all(other);
    }

    List &operator=(const List& rhs)
    {
        clear();
        copy_all(rhs);
        return *this;
    }

  //EFFECTS:  returns true if the list is empty
    bool empty() const
    {
        return numElements == 0;
    }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
    int size() const
    {
        return numElements;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
    T& front()
    {
        return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
    T& back()
    {
        return last->datum;
  }

  //EFFECTS:  inserts datum into the front of the list
    void push_front(const T& datum)
    {
        Node* p = new Node;
        p->datum = datum;
        if (!empty())
        {
            first->prev = p;
        }
        p->next = first;
        first = p;
        first->prev = nullptr;
        if (empty())
        {
            last = p;
        }
        numElements++;
  }

  //EFFECTS:  inserts datum into the back of the list
    void push_back(const T& datum)
    {
        Node* p = new Node;
        p->datum = datum;
        if (!empty())
        {
            last->next = p;
            p->prev = last;
        }
        last = p;
        p->next = nullptr;
        if (empty())
        {
            p->prev = nullptr;
            first = p;
        }
        numElements++;

  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front()
  {
      Node* victim = first;
      first = first->next;
      if (first != nullptr)
      {
          first->prev = nullptr;
      }
      delete victim;
      if (first == nullptr)
      {
          last = nullptr;
      }
      numElements--;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back()
  {
      Node* victim = last;
      if (last->prev != nullptr)
      {
          last = last->prev;
      }
      last->next = nullptr;
      delete victim;
      numElements--;
     
  }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear()
  {
      while (!empty())
      {
          pop_front();
      }
  }

  ~List()
  {
      clear();
  }

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T>& other)
  {
      for (T i : other)
      {
          push_back(i);
      }
  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty
  int numElements;

public:
  ////////////////////////////////////////
  class Iterator {

  public:
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator-- () {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

 
    Iterator()
    {
        node_ptr = nullptr;
        // past the end by default
    }

    T& operator* () const
    {
        return node_ptr->datum;
    }
    T* operator->() const
    {
        return &node_ptr->datum;
    }
    bool operator==(const Iterator& other) const
    {
        return node_ptr == other.node_ptr;
    }
    bool operator!=(Iterator rhs) const
    {
        return node_ptr != rhs.node_ptr;
    }

    Iterator& operator++ ()
    {
        node_ptr = node_ptr->next;
        return *this;
    }

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here
    friend class List;
    // construct an Iterator at a specific position
    Iterator(Node* p) : node_ptr(p)
    {
        
    }

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const
  {
      return Iterator();
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i)
  {
      if (i.node_ptr->prev != nullptr)
      {
          i.node_ptr->prev->next = i.node_ptr->next;
      }
      if (i.node_ptr->next != nullptr)
      {
          i.node_ptr->next->prev = i.node_ptr->prev;
      }
      if (i.node_ptr == last)
      {
          last = i.node_ptr->prev;
      }
      if (i.node_ptr == first)
      {
          first = i.node_ptr->next;
      }
      delete i.node_ptr;
      numElements--;
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T& datum)
  {
      if (i == begin())
      {
          push_front(datum);
          return;
      }
      if (i == end())
      {
          push_back(datum);
          return;
      }
      Node* n = new Node;
      n->datum = datum;
      n->prev = i.node_ptr->prev;
      i.node_ptr->prev->next = n;
      n->next = i.node_ptr;
      i.node_ptr->prev = n;
      numElements++;
  }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.
