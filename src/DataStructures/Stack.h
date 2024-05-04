#ifndef SELDA_STACK_H
#define SELDA_STACK_H

#include <iostream>
#include <string>

using namespace std;

#define SIZE 1900

template <class T> class Stack {
public:
    Stack();

    void push(T data);

    T pop();

    T top();

    bool empty();

    bool full();

private:
    int top_element;
    T st[SIZE];
};

template <class T> Stack<T>::Stack() {
    top_element = -1;
}

template <class T> void Stack<T>::push(T data) {
    if (full()) {
        cout << "Stack is full" << endl;
    }
    top_element = top_element + 1;
    st[top_element] = data;
}

template <class T> bool Stack<T>::empty() {
    if (top_element == -1) {
        return true;
    } else {
        return false;
    }
}

template <class T> bool Stack<T>::full() {
    if (top_element == SIZE - 1) {
        return true;
    } else {
        return false;
    }
}

template <class T> T Stack<T>::pop() {
    T popped = st[top_element];
    top_element--;
    return popped;
}

template <class T> T Stack<T>::top() {
    return st[top_element];
}

#endif //SELDA_STACK_H
