#include <utility>
#include <stdexcept>

/**
 * @brief A template generic Stack class with fixed capacity.
 *
 * The stack supports basic operations such as push, pop, and top, as well as
 * copy and move of the stack.
 *
 * @tparam T The type of elements in the stack.
 */
template <typename T>
class Stack {
public:
    /**
     * @brief Constructs a stack with a fixed capacity.
     *
     * @param capacity The maximum number of elements the stack can have.
     */
    explicit Stack(std::size_t capacity);

    /**
     * @brief Copy constructor. Creates a copy of the stack.
     *
     * @param other The stack to copy from.
     */
    Stack(const Stack& other);

    /**
     * @brief Move constructor. Transfers ownership of the stack's data.
     *
     * @param other The stack to move from.
     */
    Stack(Stack&& other) noexcept;

    /**
     * @brief Copy assignment operator. Copies data from another stack.
     *
     * @param other The stack to copy from.
     * @return Reference to the current stack after assignment.
     */
    Stack& operator=(const Stack& other);

    /**
     * @brief Move assignment operator. Moves data from another stack.
     *
     * @param other The stack to move from.
     * @return Reference to the current stack after assignment.
     */
    Stack& operator=(Stack&& other) noexcept;

    /**
     * @brief Destructor. Releases the allocated memory.
     */
    ~Stack();

    /**
     * @brief Pushes an element onto the stack.
     *
     * Throws an exception if the stack is full.
     *
     * @param value The element to push.
     * @throws std::runtime_error If the stack is full.
     */
    void push(const T& value);

    /**
     * @brief Pushes an element onto the stack using move semantics.
     *
     * Throws an exception if the stack is full.
     *
     * @param value The element to push.
     * @throws std::runtime_error If the stack is full.
     */
    void push(T&& value);

    /**
     * @brief Removes the top element from the stack.
     *
     * Throws an exception if the stack is empty.
     *
     * @throws std::runtime_error If the stack is empty.
     */
    void pop();

    /**
     * @brief Returns the top element of the stack.
     *
     * Throws an exception if the stack is empty.
     *
     * @return Reference to the top element.
     * @throws std::runtime_error If the stack is empty.
     */
    T& top();

    /**
     * @brief Returns the top element of the stack (const version).
     *
     * Throws an exception if the stack is empty.
     *
     * @return Const reference to the top element.
     * @throws std::runtime_error If the stack is empty.
     */
    const T& top() const;

    /**
     * @brief Checks if the stack is empty.
     *
     * @return True if the stack is empty, false otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief Returns the current number of elements in the stack.
     *
     * @return The size of the stack.
     */
    std::size_t getSize() const;

    /**
     * @brief Returns the fixed capacity of the stack.
     *
     * @return The capacity of the stack.
     */
    std::size_t getCapacity() const;

private:

    /**
      * @brief Swaps the contents of this stack with another stack.
      *
      * @param other The other stack to swap with.
      */
    void swap(Stack& other) noexcept;

    /**
     * @brief Clears the stack and releases the dynamically allocated memory.
     */
    void clear();

    std::size_t capacity;        ///< The fixed capacity of the stack.
    std::size_t size;            ///< The current size in elements in the stack.
    T* data;                     ///< Pointer to the start of the stack memory;
};

template <typename T>
Stack<T>::Stack(std::size_t capacity) : capacity(capacity), size(0), data(new T[capacity]) {}

template <typename T>
Stack<T>::Stack(const Stack& other) : capacity(other.capacity), size(other.size), data(new T[other.capacity]) {
    for (std::size_t i = 0; i < other.size; ++i) {
        data[i] = other.data[i];
    }
}

template <typename T>
Stack<T>::Stack(Stack&& other) noexcept : capacity(0), size(0), data(nullptr) {
    swap(other);
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
    if (this != &other) {
        Stack temp(other);
        swap(temp);
    }
    return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& other) noexcept {
    if (this != &other) {
        clear();
        swap(other);
    }
    return *this;
}

template <typename T>
Stack<T>::~Stack() {
    clear();
}

template <typename T>
void Stack<T>::push(const T& value) {
    if (size >= capacity) {
        throw std::runtime_error("Stack overflow: Stack is full.");
    }
    data[size++] = value;
}

template <typename T>
void Stack<T>::push(T&& value) {
    if (size >= capacity) {
        throw std::runtime_error("Stack overflow: Stack is full.");
    }
    data[size++] = std::move(value);
}

template <typename T>
void Stack<T>::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty.");
    }
    --size;
}

template <typename T>
T& Stack<T>::top() {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty.");
    }
    return data[size - 1];
}

template <typename T>
const T& Stack<T>::top() const {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty.");
    }
    return data[size - 1];
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return size == 0;
}

template <typename T>
std::size_t Stack<T>::getSize() const {
    return size;
}

template <typename T>
std::size_t Stack<T>::getCapacity() const {
    return capacity;
}

template <typename T>
void Stack<T>::swap(Stack& other) noexcept {
    std::swap(capacity, other.capacity);
    std::swap(size, other.size);
    std::swap(data, other.data);
}

template <typename T>
void Stack<T>::clear() {
    delete[] data;
    data = nullptr;
    size = 0;
}