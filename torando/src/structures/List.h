#ifndef LIST_H_
#define LIST_H_

//[]------------------------------------------------------------------------[]
//|                                                                          |
//|                        Small Size League software                        |
//|                             Version 1.0                                  |
//|                     Laboratório de Inteligencia Artificial				 |
//| 				 Universidade Federal de Mato Grosso do Sul              |
//|					 Author: Bruno H. Gouveia, Yuri Claure					 |
//|																			 |
//[]------------------------------------------------------------------------[]
//
//  OVERVIEW: List.h
//  ========
//  Class definition for list.

#include <stdlib.h>

template<typename T>
class ListNode;
template<typename T>
class ListIterator;

//////////////////////////////////////////////////////////
//
// List: list class template
// ==========
template<typename T>
class List {
	public:
		List();
		virtual ~List();

		bool add(const ListNode<T> & node);
		bool add(const List<T> & list);

		bool remove(const T & value);

		ListIterator<T> * getIterator();

	private:
		int size;
		List(const List<T> &);
		List<T> & operator=(const List<T>&);
};


//////////////////////////////////////////////////////////
//
// ListNode: list node class template
// ==========
template<typename T>
class ListNode {
	private:
		friend class List<T> ;

		ListNode(const T & value, const ListNode<T> & next = NULL);
		~ListNode();

		T & value;
		ListNode<T> * next;
};

//////////////////////////////////////////////////////////
//
// ListIterator: list iterator class template
// ==========
template<typename T>
class ListIterator {
	public:
		void moveBegin();

		bool hasNext();
		const T & getNext();

	private:
		friend class List<T> ;

		ListIterator();
		~ListIterator();
};

//////////////////////////////////////////////////////////
//
// List implementation
// ==========
template<typename T>
List<T>::List() {

}
template<typename T>
List<T>::~List() {

}

template<typename T>
bool List<T>::add(const ListNode<T> & node) {
	return false;
}
template<typename T>
bool List<T>::add(const List<T> & list) {
	return false;
}

template<typename T>
bool List<T>::remove(const T & value) {
	return false;
}

template<typename T>
ListIterator<T> * List<T>::getIterator() {
	return NULL;
}


//////////////////////////////////////////////////////////
//
// ListNode implementation
// ==========
template<typename T>
ListNode<T>::ListNode(const T & value, const ListNode<T> & next) :
		value(value), next(next) {

}
template<typename T>
ListNode<T>::~ListNode() {
}

//////////////////////////////////////////////////////////
//
// ListIterator implementation
// ==========
template<typename T>
void ListIterator<T>::moveBegin() {

}
template<typename T>
bool ListIterator<T>::hasNext() {
	return false;
}
template<typename T>
const T & ListIterator<T>::getNext() {
	return NULL;
}

template<typename T>
ListIterator<T>::ListIterator() {

}
template<typename T>
ListIterator<T>::~ListIterator() {

}

#endif /* LIST_H_ */
