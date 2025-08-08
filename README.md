# **C++ Smart Pointer Training Project**  

**University Assignment | Dungeons & Dragons-Themed Example**  

## **Project Overview**  
A C++ training project designed to practice modern memory management using smart pointers (`std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`). The code structure uses a simplified Dungeons & Dragons theme to model object ownership and resource management.  

### **Key Concepts Demonstrated**  
✔ Proper use of smart pointers to avoid memory leaks  
✔ Object ownership semantics in OOP design  
✔ Resource management in a multi-entity system  

## **Technical Details**  

### **Dependencies**  
- C++17 or later  
- CMake (optional, for build automation)  



### **Smart Pointer Usage Examples**  
| Use Case               | Pointer Type       | Rationale                          |  
|------------------------|--------------------|------------------------------------|   
| Party-shared campaign  | `std::shared_ptr`  | Multiple access with ref-counting  |  
| Observer references    | `std::weak_ptr`    | Avoid circular dependencies        |  


## **Key Takeaways**  
- Demonstrated RAII principles via smart pointers  
- Practical examples of ownership transfer and shared access  
- Thematic but functionally clear separation of concerns  

*(Note: Dungeons & Dragons theme serves only as a naming convention—core logic is standard C++ memory management.)*  

