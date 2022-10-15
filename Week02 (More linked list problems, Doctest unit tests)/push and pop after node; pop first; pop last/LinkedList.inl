#include "LinkedList.h"
#include <iostream>

template<typename T>
inline LinkedList<T>::Node::Node(const T& data, Node* next)
{
	data_ = data;
	next_ = next;
}

template<typename T>
inline void LinkedList<T>::copy(const LinkedList& other)
{
	head_ = tail_ = nullptr;

	Node* current = other.head_;
	while (current != nullptr)
	{
		pushBack(current->data_);
		current = current->next_;
	}
}

template<typename T>
inline void LinkedList<T>::del()
{
	while (head_ != nullptr)
	{
		Node* current = head_;
		head_ = head_->next_;
		delete current;
	}
}

template<typename T>
inline LinkedList<T>::LinkedList()
	: head_(nullptr), tail_(nullptr)
{
}

template<typename T>
inline LinkedList<T>::LinkedList(const LinkedList& other)
{
	copy(other);
}

template<typename T>
inline LinkedList<T>::~LinkedList()
{
	del();
}

template<typename T>
inline const size_t LinkedList<T>::getSize() const
{
	size_t count = 0;

	Node* current = head_;
	while (current != nullptr)
	{
		current = current->next_;
		count++;
	}

	return count;
}

template<typename T>
inline void LinkedList<T>::pushBack(const T& elem)
{
	Node* nodeToAdd = new Node(elem);

	if (head_ == nullptr)
	{
		head_ = tail_ = nodeToAdd;
		return;
	}

	tail_->next_ = nodeToAdd;
	tail_ = nodeToAdd;
}

template<typename T>
inline void LinkedList<T>::updateAt(const size_t& index, const T& elem)
{
	Node* current = head_;

	for (size_t i = 0; i < index; i++)
		current = current->next_;
	current->data_ = elem;
}

template<typename T>
inline void LinkedList<T>::popAt(const size_t& index)
{
	if (index >= getSize())
		throw std::exception("Value to remove is out of bounds.\n");

	if (index == 0)
	{
		Node* tempHead = head_;
		head_ = tempHead->next_;
		delete tempHead;
		return;
	}

	Node* previousToNodeToRemove = head_;

	for (size_t i = 0; i < index - 1; i++)
		previousToNodeToRemove = previousToNodeToRemove->next_;

	Node* nodeToRemove = previousToNodeToRemove->next_;
	previousToNodeToRemove->next_ = nodeToRemove->next_;
	delete nodeToRemove;
}

template<typename T>
inline T LinkedList<T>::operator[](const size_t& index) const
{
	Node* current = head_;
	size_t count = index;

	while (current != nullptr && count-- > 0)
	{
		current = current->next_;
	}

	return (current == nullptr ? T() : current->data_);
}

template<typename T>
inline void LinkedList<T>::pushAfterNode(const T& value, Node* iterator)
{
	if (iterator == nullptr)
		return;

	Node* nodeToAdd = new Node(value);
	nodeToAdd->next_ = iterator->next_;
	iterator->next_ = nodeToAdd;

	if (iterator->next_ == nullptr)
		tail_ = nodeToAdd;
}

template<typename T>
inline T LinkedList<T>::popFirst()
{
	if (head_ == nullptr)
		throw std::exception("Cannot pop from empty list.\n");

	Node* temp = head_;
	head_ = head_->next_;

	const T dataCopy = temp->data_;
	delete temp;

	return dataCopy;
}

template<typename T>
inline T LinkedList<T>::popLast()
{
	if (head_ == nullptr)
		throw std::exception("Cannot pop from empty list.\n");

	if (head_->next_ == nullptr)
	{
		Node* temp = head_;

		head_ = tail_ = nullptr;

		const T dataCopy = temp->data_;
		delete temp;
		return dataCopy;
	}

	Node* temp = tail_;

	Node* secondToLast = head_;
	while (secondToLast->next_->next_ != nullptr)
	{
		secondToLast = secondToLast->next_;
	}
	secondToLast->next_ = nullptr;
	tail_ = secondToLast;

	const T dataCopy = temp->data_;
	delete temp;

	return dataCopy;
}

template<typename T>
inline T LinkedList<T>::popAfterNode(Node* iterator)
{
	if (iterator == nullptr || iterator->next_ == nullptr)
		return T();

	Node* nodeToPop = iterator->next_;
	iterator->next_ = nodeToPop->next_;

	const T dataCopy = nodeToPop->data_;
	delete nodeToPop;

	return dataCopy;
}