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

      #include <iostream>
      #include <vector>
      using namespace std;
      
      int main() {
          // Collection: vector (dynamic array)
          vector<int> numbers = {10, 20, 30, 40, 50};
      
          // Iterator for traversing the vector
          vector<int>::iterator it;
      
          cout << "Elements in the vector:" << endl;
          for (it = numbers.begin(); it != numbers.end(); ++it) {
              cout << *it << " "; // Dereferencing iterator to access the value
          }
          cout << endl;
      
          // Using a range-based loop (modern alternative to iterators)
          cout << "Using range-based loop:" << endl;
          for (int num : numbers) {
              cout << num << " ";
          }
          cout << endl;
      
          return 0;
      }

## 8. Composition vs Inheritance
- Composition "has-a" class containing an object of another class as a member.
- Inheritance "is-a" mechanism where a class (child) derives properties and behaviors from another class (parent).

<img src="https://github.com/user-attachments/assets/58c76530-a2e5-40f9-85cf-5efb53f0be25" width=450>

## 9. Constructors and Destructors
- **Constructors**: Special methods that initialize an object when it is created.
- **Destructors**: Methods called when an object is destroyed to release resources.

      #include <iostream>
      using namespace std;
      
      class Car {
      private:
          string model;
          int year;
      
      public:
          // Constructor
          Car(string m, int y) {
              model = m;
              year = y;
              cout << "Car object created: " << model << " (" << year << ")" << endl;
          }
      
          // Destructor
          ~Car() {
              cout << "Car object destroyed: " << model << " (" << year << ")" << endl;
          }
      
          // Member function to display car info
          void displayInfo() {
              cout << "Model: " << model << ", Year: " << year << endl;
          }
      };
      
      int main() {
          // Creating objects using the constructor
          Car car1("Toyota", 2020);  // Constructor called
          car1.displayInfo();
      
          {
              Car car2("Honda", 2022);  // Constructor called for car2
              car2.displayInfo();
          } // car2 goes out of scope and destructor is called here
      
          return 0;  // car1 goes out of scope and its destructor is called here
      }


## 10. Design Patterns
- **Singleton**: Ensures a class has only one instance and provides a global point of access to it.

      #include <iostream>
      #include <mutex>
      
      class Singleton {
      private:
          static Singleton* instance;
          static std::mutex mutex_;
      
          // Private constructor to prevent instantiation
          Singleton() {}
      
      public:
          // Delete copy constructor and assignment operator
          Singleton(const Singleton&) = delete;
          Singleton& operator=(const Singleton&) = delete;
      
          static Singleton* getInstance() {
              std::lock_guard<std::mutex> lock(mutex_);
              if (instance == nullptr) {
                  instance = new Singleton();
              }
              return instance;
          }
      
          void showMessage() {
              std::cout << "Singleton instance accessed!\n";
          }
      };
      
      // Initialize static members
      Singleton* Singleton::instance = nullptr;
      std::mutex Singleton::mutex_;
      
      int main() {
          Singleton* singleton = Singleton::getInstance();
          singleton->showMessage();
          return 0;
      }

- **Factory**: Provides an interface for creating objects without specifying their exact class.

      #include <iostream>
      #include <memory>
      
      // Product interface
      class Product {
      public:
          virtual void operation() const = 0;
          virtual ~Product() = default;
      };
      
      // Concrete products
      class ConcreteProductA : public Product {
      public:
          void operation() const override {
              std::cout << "Operation from ConcreteProductA\n";
          }
      };
      
      class ConcreteProductB : public Product {
      public:
          void operation() const override {
              std::cout << "Operation from ConcreteProductB\n";
          }
      };
      
      // Factory class
      class Factory {
      public:
          static std::unique_ptr<Product> createProduct(const std::string& type) {
              if (type == "A") {
                  return std::make_unique<ConcreteProductA>();
              } else if (type == "B") {
                  return std::make_unique<ConcreteProductB>();
              }
              return nullptr;
          }
      };
      
      int main() {
          auto productA = Factory::createProduct("A");
          auto productB = Factory::createProduct("B");
      
          if (productA) productA->operation();
          if (productB) productB->operation();
      
          return 0;
      }

- **Observer**: Defines a one-to-many dependency, where changes in one object notify all dependent objects.

      #include <iostream>
      #include <vector>
      #include <memory>
      
      // Subject (Observable)
      class Subject {
          std::vector<class Observer*> observers;
      
      public:
          void attach(Observer* observer) {
              observers.push_back(observer);
          }
      
          void notify() {
              for (Observer* observer : observers) {
                  observer->update();
              }
          }
      };
      
      // Observer
      class Observer {
      public:
          virtual void update() = 0;
          virtual ~Observer() = default;
      };
      
      // Concrete Observers
      class ConcreteObserverA : public Observer {
      public:
          void update() override {
              std::cout << "ConcreteObserverA notified!\n";
          }
      };
      
      class ConcreteObserverB : public Observer {
      public:
          void update() override {
              std::cout << "ConcreteObserverB notified!\n";
          }
      };
      
      int main() {
          Subject subject;
      
          ConcreteObserverA observerA;
          ConcreteObserverB observerB;
      
          subject.attach(&observerA);
          subject.attach(&observerB);
      
          std::cout << "Notifying observers...\n";
          subject.notify();
      
          return 0;
      }

## 11. Encapsulation
- Bundling data (attributes) and methods that operate on the data into a single unit (class) and restricting direct access to them.

![image](https://github.com/user-attachments/assets/efa85c79-ac83-4989-86e5-9e92fec5bb36)

## 12. Exception Handling
- Mechanisms for handling runtime errors, typically using constructs like `try`, `catch`, and `finally`.

      #include <iostream>
      
      double divide(double numerator, double denominator) {
          if (denominator == 0) {
              throw std::runtime_error("Division by zero!");
          }
          return numerator / denominator;
      }
      
      int main() {
          try {
              double result = divide(10, 0);  // Will throw an exception
              std::cout << "Result: " << result << std::endl;
          } catch (const std::runtime_error& e) {
              std::cout << "Caught exception: " << e.what() << std::endl;
          }
      
          return 0;
      }

## 13. File I/O in OOP
- File operations (read/write) managed using object-oriented concepts, often encapsulated in classes for better modularity and error handling.

      #include <iostream>
      #include <fstream>
      #include <string>
      
      class FileHandler {
      private:
          std::string fileName;
          std::fstream fileStream;
      
      public:
          // Constructor to set file name
          explicit FileHandler(const std::string& name) : fileName(name) {}
      
          // Method to write data to the file
          void write(const std::string& data) {
              fileStream.open(fileName, std::ios::out | std::ios::app); // Open in append mode
              if (!fileStream) {
                  throw std::ios_base::failure("Failed to open file for writing.");
              }
              fileStream << data << "\n";
              fileStream.close();
          }
      
          // Method to read data from the file
          void read() {
              fileStream.open(fileName, std::ios::in); // Open in read mode
              if (!fileStream) {
                  throw std::ios_base::failure("Failed to open file for reading.");
              }
      
              std::string line;
              while (std::getline(fileStream, line)) {
                  std::cout << line << std::endl;
              }
              fileStream.close();
          }
      
          // Destructor to ensure file is closed
          ~FileHandler() {
              if (fileStream.is_open()) {
                  fileStream.close();
              }
          }
      };
      
      int main() {
          try {
              FileHandler file("example.txt");
      
              file.write("Hello, World!");
              file.write("This is a sample file.");
              
              std::cout << "File Contents:" << std::endl;
              file.read();
          } catch (const std::exception& e) {
              std::cerr << "Error: " << e.what() << std::endl;
          }
      
          return 0;
      }

## 14. Friends
- A concept in some languages (e.g., C++) where a class or function is declared as a "friend" to access private/protected members of another class.

      #include <iostream>
      
      class Number {
      private:
          int value;
      
      public:
          // Constructor
          explicit Number(int v) : value(v) {}
      
          // Declaring friend function
          friend int add(const Number& num1, const Number& num2);
      };
      
      // Definition of the friend function
      int add(const Number& num1, const Number& num2) {
          return num1.value + num2.value; // Accessing private members
      }
      
      int main() {
          Number n1(10);
          Number n2(20);
      
          std::cout << "Sum: " << add(n1, n2) << std::endl;
      
          return 0;
      }

## 15. Generics and Templates
- **Generics**: Allow classes and methods to operate on types specified at runtime (e.g., Java Generics).
- **Templates**: Similar to generics but used at compile time (e.g., C++ Templates).

## 16. Instance Variable
- A variable tied to a specific instance of a class, holding unique values for each object.

## 17. Member Variable
- Variables defined within a class and can be either instance or class variables.

## 18. Memory Management (Garbage Collection, Pointers)
- **Garbage Collection**: Automatic memory management that reclaims unused objects.
- **Pointers**: Variables that store memory addresses (commonly used in C++).

## 19. Method Overloading
- Defining multiple methods in the same class with the same name but different parameters.

## 20. Method
- A function defined within a class that operates on the class's data.

## 21. Multiple Inheritance
- A class inheriting from more than one parent class, which can lead to complexity (e.g., the "diamond problem").

## 22. Multithreading in OOP
- Using threads to execute multiple tasks concurrently, often handled with OOP principles for better modularity and synchronization.

## 23. Object Relationships (Association, Aggregation, Composition)
- **Association**: A general relationship between objects.
- **Aggregation**: A "has-a" relationship where contained objects can exist independently.
- **Composition**: A stronger "has-a" relationship where contained objects depend on the container.

## 24. Object-Oriented Design Principles
- Guidelines like SOLID, DRY, and KISS that promote good design practices.

## 25. Operator Overloading
- Redefining the behavior of operators for user-defined types.

## 26. Overloading
- Providing multiple methods with the same name but different parameters or types.

## 27. Polymorphism
- The ability to process objects differently based on their data type or class, commonly achieved through method overriding and overloading.

## 28. Public / Private / Protected
- Refer to **Access Modifiers**.

## 29. SOLID Principles
Principles for maintainable OOP design.
- **S**ingle Responsibility
- **O**pen/Closed
- **L**iskov Substitution
- **I**nterface Segregation
- **D**ependency Inversion

## 30. Static (Methods and Variables)
- **Static Variables**: Shared among all class instances.
- **Static Methods**: Methods that belong to the class rather than any instance.

## 31. Testing in OOP
- **Unit Testing**: Testing individual components of code.
- **Test-Driven Development**: Writing tests before implementing functionality.

## 32. UML Diagrams and Modeling
- Unified Modeling Language diagrams like class, sequence, and activity diagrams to design and visualize OOP systems.

## 33. Virtual
- A keyword in languages like C++ to enable method overriding in derived classes, supporting runtime polymorphism.
