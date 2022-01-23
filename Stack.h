#pragma once
#include <stdexcept>
#include <utility>

template <typename T>
class Stack
{
private:
	//элемент стека
	struct el {
		T value; //значение элемента
		el* pre; //указатель на предыдущий элемент
	};
	size_t _size; //размер стека
	el* _head; //указатель на верхний элемент
public:
	//пустой стек
	Stack() : _head(nullptr), _size(0) {};

	void push(T&& value); 
	void push(const T& value); 
	void pop(); //удалить верхний элемент
	T _pop(); //сн€тие первого элемента
	const T& head() const; //получить верхушку

	template <typename ... Args>
	void push_emplace(Args&&... value);
};

template <typename T>
void Stack<T>::push(T&& value) {
	_head = new el{ std::move(value), _head }; //правосторонн€€ ссыдка -> std::move
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
	_head = new el{ T{std::forward<Args>(value)...}, _head };  //forward в л ссылки 
	++_size;
}

template <typename T>
T Stack<T>::_pop() {
	const T& val = head();
	pop();
	return *val;
}

