#pragma once
#include <stdexcept>
#include <utility>

template <typename T>
class Stack
{
private:
	//������� �����
	struct el {
		T value; //�������� ��������
		el* pre; //��������� �� ���������� �������
	};
	size_t _size; //������ �����
	el* _head; //��������� �� ������� �������
public:
	//������ ����
	Stack() : _head(nullptr), _size(0) {};
	~Stack();
	//����������� �����������
	Stack(const Stack&) = delete;
	//�������� �����������
	Stack& operator=(const Stack&) = delete;

	//����������� �����������
	Stack(Stack&& stack) noexcept;
	//�������� �����������
	Stack& operator=(Stack&& stack) noexcept;

	void push(T&& value); 
	void push(const T& value); 
	void pop(); //������� ������� �������
	T _pop(); //������ ������� ��������
	const T& head() const; //�������� ��������

	template <typename ... Args>
	void push_emplace(Args&&... value);

	//void swap()
};

template <typename T>
Stack<T>::Stack(Stack&& stack) noexcept {
	_size = std::move(stack._size);
	_head = std::move(stack._head);
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& stack) noexcept {
	if (&stack != this) {
		std::swap(_size, stack._size);
		std::swap(_head, stack._head);
	}
	return *this;
}

template <typename T>
Stack<T>::~Stack() {
	auto i = _head;
	while (i != nullptr) {
		auto new_i = i->pre;
		delete i;
		i = new_i;
	}
}

template <typename T>
void Stack<T>::push(T&& value) {
	_head = new el{ std::move(value), _head }; //�������������� ������ -> std::move
	++_size;
}

template <typename T>
void Stack<T>::push(const T& value) {
	_head = new el{ value, _head };
	++_size;
}

template <typename T>
void Stack<T>::pop() {
	auto const old_head = _head;
	if (old_head == nullptr) return;

	auto new_head = old_head->pre;
	if (new_head == nullptr) {
		_head = nullptr;
		_size = 0;
	}
	else {
		_head = new_head;
		--_size;
	}
	delete old_head;
}

template <typename T>
const T& Stack<T>::head() const {
	if (_head == nullptr) {
		throw std::out_of_range("Stack is empty. No head.\n");
	}
	return _head->value;
}

template <typename T>
template <typename ... Args>
void Stack<T>::push_emplace(Args&&... value) {
	for (auto i : { std::forward<Args>(value)... }) {
		_head = new el{ std::move(i), _head }; //�������������� ������ -> std::move
		++_size;
	}
}

template <typename T>
T Stack<T>::_pop() {
	T val = head();
	pop();
	return val;
}

