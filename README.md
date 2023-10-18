# ft_containers - C++ Containers Reimplementation

## Overview
The **ft_containers** project is a comprehensive reimplementation of several container types from the C++ Standard Template Library (STL). This project is designed to deepen your understanding of the inner workings of STL containers and how to efficiently implement them. By recreating these containers, you will gain insights into the core principles of data structures and algorithms in C++.

## Containers Implemented
This project covers the following containers:

1. **vector**
2. **map**
3. **stack**
4. **set**

## Requirements
To ensure the project's success, adhere to the following requirements:

### Namespace
- The namespace for your containers must be named **ft**.

### Logical Data Structures
- We use Red-Black tree Data Structure to implement map and set
### Public Functions and Variables
- You cannot introduce more public functions than those offered in the standard containers. Any additional functions or variables must be private or protected, and their inclusion must be justified.

### Functionality
- Implement all the member functions, non-member functions, and overloads found in the standard containers. Maintain the original naming conventions to ensure compatibility.

### Iterator System
- If the standard container has an iterator system, it must be implemented. Iterators are crucial for the functionality of the containers.

### std::allocator
- The implementation should utilize `std::allocator` for memory management, ensuring efficient memory allocation and deallocation.

### Friend Keyword
- For non-member function overloads, you may use the `friend` keyword. Each use of the `friend` keyword should be justified and will be evaluated during the assessment. For instance, you are allowed to use `friend` for the implementation of `std::map::value_compare`.

## Additional Explanations
- This project is an opportunity to gain a deep understanding of the internal workings of C++ containers. You will learn how to manage memory efficiently, handle data storage, and implement key functionality.
- The project enforces adherence to the naming and public function requirements of the standard containers to ensure that the reimplementation is compatible with the STL.
- The use of data structures should be well-justified, reflecting your understanding of when and why certain data structures are chosen for specific container types.
- The `friend` keyword is allowed for non-member overloads but should be used judiciously and with clear justification. Its usage will be reviewed during evaluation.
- This project provides a comprehensive and educational experience in understanding C++ containers and data structure design, preparing you for more advanced programming tasks.
