# A04

### Jack Leary
### 12/06/2024
### 2143 OOP

## 1. Abstract Classes and Interfaces
- **Abstract Classes**: Classes that cannot be instantiated directly and are used to define a common base class with abstract methods that must be implemented in derived classes.

      #include <iostream>
      using namespace std;
      
      // Abstract class
      class Shape {
      public:
          virtual void draw() const = 0; // Pure virtual function
          virtual ~Shape() {}           // Virtual destructor
      };
      
      // Derived class
      class Circle : public Shape {
      public:
          void draw() const override {
              cout << "Drawing a Circle" << endl;
          }
      };
      
      int main() {
          Shape* circle = new Circle();
          circle->draw(); // Output: Drawing a Circle
          delete circle;
          return 0;
      }

- **Interfaces**: Contracts that define a set of methods that implementing classes must provide. Unlike abstract classes, interfaces do not contain implementation details.

  <img src="https://github.com/user-attachments/assets/91487bc8-a300-4e8b-b3e8-86e37dc3e20b" width=350>

## 2. Abstraction
- The process of hiding implementation details and showing only essential features of an object. It focuses on "what" an object does rather than "how" it does it.

## 3. Access Modifiers (Public, Private, Protected)
- **Public**: Members are accessible from anywhere.
- **Private**: Members are accessible only within the same class.
- **Protected**: Members are accessible within the same class and by derived classes.

      #include <iostream>
      using namespace std;

      class Base {
      private:
        int privateVar = 1; // Only accessible within this class
    
      protected:
          int protectedVar = 2; // Accessible within this class and derived classes
  
      public:
          int publicVar = 3; // Accessible from anywhere
  
      void showMembers() {
          cout << "Private: " << privateVar << ", Protected: " << protectedVar 
               << ", Public: " << publicVar << endl;
      }
  
      class Derived : public Base {
      public:
      void accessBaseMembers() {
          privateVar = 10;   // Error: privateVar is not accessible
          protectedVar = 20; // Accessible because it's protected
          publicVar = 30;    // Accessible because it's public
      }
      };
  
      int main() {
          Base base;
          base.publicVar = 5; // Allowed
          // base.protectedVar = 15; // Error: protectedVar is not accessible here
          // base.privateVar = 10;   // Error: privateVar is not accessible here
    
        base.showMembers(); // Accesses all members within the Base class
    
        Derived derived;
        derived.accessBaseMembers();
        derived.publicVar = 50; // Allowed
        // derived.protectedVar = 25; // Error: protectedVar is not accessible directly
        derived.showMembers();
    
        return 0;
        }


## 4. Attributes / Properties
- **Attributes**: Characteristics or data stored within an object, typically represented as variables.
- **Properties**: A special type of attribute with getters and setters for controlled access.

  <img src="https://github.com/user-attachments/assets/8f0938c6-ec7e-4dc8-b834-e3c758ce8c98" width=450>


## 5. Class Variable
- A variable that is shared among all instances of a class, declared with the `static` keyword in many languages.

      class Counter {
      private:
          static int count; // Class variable (shared by all instances)
      
      public:
          Counter() {
              count++;
          }

          ~Counter() {
              count--;
          }
      
          static int getCount() { // Static member function to access class variable
              return count;
          }
      };

## 6. Classes and Objects
- **Class**: A blueprint for creating objects, defining their attributes and behaviors.
- **Object**: An instance of a class, representing a specific entity.
<img src="https://ds055uzetaobb.cloudfront.net/image_optimizer/722c82aff075a14313be7fa7463f7fedad151a0a.png" width=250>

## 7. Collections and Iterators
- **Collections**: Data structures like arrays, lists, sets, and maps used to store groups of objects.
- **Iterators**: Objects that enable sequential traversal of elements in a collection.

## 8. Composition
- A "has-a" relationship where one class contains an object of another class as a member.

## 9. Constructors and Destructors
- **Constructors**: Special methods that initialize an object when it is created.
- **Destructors**: Methods called when an object is destroyed to release resources.

## 10. Design Patterns
- **Singleton**: Ensures a class has only one instance and provides a global point of access to it.
- **Factory**: Provides an interface for creating objects without specifying their exact class.
- **Observer**: Defines a one-to-many dependency, where changes in one object notify all dependent objects.

## 11. Encapsulation
- Bundling data (attributes) and methods that operate on the data into a single unit (class) and restricting direct access to them.

## 12. Exception Handling
- Mechanisms for handling runtime errors, typically using constructs like `try`, `catch`, and `finally`.

## 13. File I/O in OOP
- File operations (read/write) managed using object-oriented concepts, often encapsulated in classes for better modularity and error handling.

## 14. Friends
- A concept in some languages (e.g., C++) where a class or function is declared as a "friend" to access private/protected members of another class.

## 15. Generics and Templates
- **Generics**: Allow classes and methods to operate on types specified at runtime (e.g., Java Generics).
- **Templates**: Similar to generics but used at compile time (e.g., C++ Templates).

## 16. Inheritance
- A mechanism where a class (child) derives properties and behaviors from another class (parent).

## 17. Instance Variable
- A variable tied to a specific instance of a class, holding unique values for each object.

## 18. Member Variable
- Variables defined within a class and can be either instance or class variables.

## 19. Memory Management (Garbage Collection, Pointers)
- **Garbage Collection**: Automatic memory management that reclaims unused objects.
- **Pointers**: Variables that store memory addresses (commonly used in C++).

## 20. Method Overloading
- Defining multiple methods in the same class with the same name but different parameters.

## 21. Method
- A function defined within a class that operates on the class's data.

## 22. Multiple Inheritance
- A class inheriting from more than one parent class, which can lead to complexity (e.g., the "diamond problem").

## 23. Multithreading in OOP
- Using threads to execute multiple tasks concurrently, often handled with OOP principles for better modularity and synchronization.

## 24. Object Relationships (Association, Aggregation, Composition)
- **Association**: A general relationship between objects.
- **Aggregation**: A "has-a" relationship where contained objects can exist independently.
- **Composition**: A stronger "has-a" relationship where contained objects depend on the container.

## 25. Object-Oriented Design Principles
- Guidelines like SOLID, DRY, and KISS that promote good design practices.

## 26. Operator Overloading
- Redefining the behavior of operators for user-defined types.

## 27. Overloading
- Providing multiple methods with the same name but different parameters or types.

## 28. Polymorphism
- The ability to process objects differently based on their data type or class, commonly achieved through method overriding and overloading.

## 29. Public / Private / Protected
- Refer to **Access Modifiers**.

## 30. SOLID Principles
- **S**ingle Responsibility, **O**pen/Closed, **L**iskov Substitution, **I**nterface Segregation, **D**ependency Inversion: Principles for maintainable OOP design.

## 31. Static (Methods and Variables)
- **Static Variables**: Shared among all class instances.
- **Static Methods**: Methods that belong to the class rather than any instance.

## 32. Testing in OOP
- **Unit Testing**: Testing individual components of code.
- **Test-Driven Development**: Writing tests before implementing functionality.

## 33. UML Diagrams and Modeling
- Unified Modeling Language diagrams like class, sequence, and activity diagrams to design and visualize OOP systems.

## 34. Virtual
- A keyword in languages like C++ to enable method overriding in derived classes, supporting runtime polymorphism.
