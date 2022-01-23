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

	void push(T&& value); 
	void push(const T& value); 
	void pop(); //������� ������� �������
	T _pop(); //������ ������� ��������
	const T& head() const; //�������� ��������

	template <typename ... Args>
	void push_emplace(Args&&... value);
};

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
	_head = new el{ T{std::forward<Args>(value)...}, _head };  //forward � � ������ 
	++_size;
}

template <typename T>
T Stack<T>::_pop() {
	const T& val = head();
	pop();
	return *val;
}

