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

      #include <iostream>
      
      // Define a generic function using a template
      template <typename T>
      T findMax(T a, T b) {
          return (a > b) ? a : b;
      }
      
      int main() {
          std::cout << "Max of 10 and 20: " << findMax(10, 20) << std::endl;  // Integers
          std::cout << "Max of 3.14 and 2.71: " << findMax(3.14, 2.71) << std::endl; // Doubles
          std::cout << "Max of 'A' and 'B': " << findMax('A', 'B') << std::endl; // Characters
      
          return 0;
      }

## 16. Instance Variable
- A variable tied to a specific instance of a class, holding unique values for each object.

      #include <iostream>
      #include <string>
      
      class Person {
      private:
          // Instance variables
          std::string name;
          int age;
      
      public:
          // Constructor to initialize instance variables
          Person(const std::string& n, int a) : name(n), age(a) {}
      
          // Getter for name
          std::string getName() const {
              return name;
          }
      
          // Setter for name
          void setName(const std::string& n) {
              name = n;
          }
      
          // Getter for age
          int getAge() const {
              return age;
          }
      
          // Setter for age
          void setAge(int a) {
              age = a;
          }
      
          // Method to display person details
          void displayInfo() const {
              std::cout << "Name: " << name << ", Age: " << age << std::endl;
          }
      };
      
      int main() {
          // Create two instances of Person
          Person person1("Alice", 30);
          Person person2("Bob", 25);
      
          // Access and modify instance variables
          person1.displayInfo();  // Name: Alice, Age: 30
          person2.displayInfo();  // Name: Bob, Age: 25
      
          person1.setName("Alice Smith");
          person1.setAge(31);
      
          // Display updated details
          person1.displayInfo();  // Name: Alice Smith, Age: 31
      
          return 0;
      }

## 17. Member Variable
- Variables defined within a class and can be either instance or class variables.

      #include <iostream>
      #include <string>
      
      class Car {
      private:
          // Member variables (Instance variables)
          std::string brand;
          int year;
      
          // Static member variable (shared among all instances)
          static int totalCars;
      
      public:
          // Constructor to initialize member variables
          Car(const std::string& b, int y) : brand(b), year(y) {
              totalCars++; // Increment total cars count
          }
      
          // Destructor to manage cleanup
          ~Car() {
              totalCars--; // Decrement total cars count
          }
      
          // Getters for instance variables
          std::string getBrand() const {
              return brand;
          }
      
          int getYear() const {
              return year;
          }
      
          // Static member function to access static variable
          static int getTotalCars() {
              return totalCars;
          }
      };
      
      // Initialize the static member variable
      int Car::totalCars = 0;
      
      int main() {
          // Create car objects
          Car car1("Toyota", 2021);
          Car car2("Ford", 2020);
      
          // Access instance variables using object methods
          std::cout << "Car 1: " << car1.getBrand() << " (" << car1.getYear() << ")" << std::endl;
          std::cout << "Car 2: " << car2.getBrand() << " (" << car2.getYear() << ")" << std::endl;
      
          // Access static member variable
          std::cout << "Total cars: " << Car::getTotalCars() << std::endl;
      
          return 0;
      }

## 18. Memory Management (Garbage Collection, Pointers)
- **Garbage Collection**: Automatic memory management that reclaims unused objects (must be manually implemented in C++)
- **Pointers**: Variables that store memory addresses (commonly used in C++).

      #include <iostream>
      
      class Car {
      public:
          std::string brand;
          int year;
      
          // Constructor
          Car(const std::string& b, int y) : brand(b), year(y) {
              std::cout << "Car " << brand << " (" << year << ") created." << std::endl;
          }
      
          // Destructor
          ~Car() {
              std::cout << "Car " << brand << " (" << year << ") destroyed." << std::endl;
          }
      };
      
      int main() {
          // Dynamically allocate memory for a Car object
          Car* carPtr = new Car("Toyota", 2021); // Allocates memory on the heap
      
          // Access the Car object using the pointer
          std::cout << "Car brand: " << carPtr->brand << ", Year: " << carPtr->year << std::endl;
      
          // Deallocate the memory when done
          delete carPtr;  // Frees the memory allocated by `new`
      
          // Note: After delete, `carPtr` is a dangling pointer. It's good practice to set it to nullptr.
          carPtr = nullptr;
      
          return 0;
      }

## 19. Method Overloading
- Defining multiple methods in the same class with the same name but different parameters.

      #include <iostream>
      using namespace std;
      
      class Calculator {
      public:
          // Method to add two integers
          int add(int a, int b) {
              return a + b;
          }
      
          // Overloaded method to add three integers
          int add(int a, int b, int c) {
              return a + b + c;
          }
      
          // Overloaded method to add two doubles
          double add(double a, double b) {
              return a + b;
          }
      };
      
      int main() {
          Calculator calc;
      
          // Calling the add method with two integers
          cout << "Sum of 2 integers: " << calc.add(10, 20) << endl;
      
          // Calling the add method with three integers
          cout << "Sum of 3 integers: " << calc.add(10, 20, 30) << endl;
      
          // Calling the add method with two doubles
          cout << "Sum of 2 doubles: " << calc.add(10.5, 20.5) << endl;
      
          return 0;
      }

## 20. Method
- A function defined within a class that operates on the class's data.

      #include <iostream>
      using namespace std;
      
      class Calculator {
      public:
          // Method to add two integers
          int add(int a, int b) {
              return a + b;
          }
      
          // Method to subtract two integers
          int subtract(int a, int b) {
              return a - b;
          }
      };

## 21. Multiple Inheritance
- A class inheriting from more than one parent class, which can lead to complexity (e.g., the "diamond problem").

<img src="https://github.com/user-attachments/assets/920947a0-0ad5-43f9-8b5f-a2c86ccbb2ea" width=550>

## 22. Multithreading in OOP
- Using threads to execute multiple tasks concurrently, often handled with OOP principles for better modularity and synchronization.

      #include <iostream>
      #include <thread>
      
      // Function that will be run on a separate thread
      void printHello() {
          std::cout << "Hello from the thread!" << std::endl;
      }
      
      // Another function for multithreading
      void printGoodbye() {
          std::cout << "Goodbye from the thread!" << std::endl;
      }
      
      int main() {
          // Create two threads
          std::thread thread1(printHello);  // Thread for printHello
          std::thread thread2(printGoodbye); // Thread for printGoodbye
      
          // Wait for both threads to finish before continuing
          thread1.join(); // Ensures the main thread waits for thread1 to finish
          thread2.join(); // Ensures the main thread waits for thread2 to finish
      
          std::cout << "Main thread is finished!" << std::endl;
      
          return 0;
      }

## 23. Object Relationships (Association, Aggregation, Composition)
- **Association**: A general relationship between objects.

      #include <iostream>
      #include <vector>
      using namespace std;
      
      // Student class
      class Student {
      public:
          void study() {
              cout << "Student is studying." << endl;
          }
      };
      
      // Teacher class
      class Teacher {
      public:
          void teach() {
              cout << "Teacher is teaching." << endl;
          }
      
          void interactWithStudent(Student& student) {
              student.study();  // Interaction between Teacher and Student (association)
          }
      };
      
      int main() {
          Student student;
          Teacher teacher;
      
          teacher.teach();
          teacher.interactWithStudent(student);
      
          return 0;
      }

- **Aggregation**: A "has-a" relationship where contained objects can exist independently.

      #include <iostream>
      #include <vector>
      using namespace std;
      
      // Professor class
      class Professor {
      public:
          void teach() {
              cout << "Professor is teaching." << endl;
          }
      };
      
      // Department class (aggregates Professors)
      class Department {
      private:
          vector<Professor*> professors;  // Professors belong to a department (aggregation)
      
      public:
          void addProfessor(Professor* professor) {
              professors.push_back(professor);
          }
      
          void showProfessors() {
              cout << "Professors in the department: " << endl;
              for (auto professor : professors) {
                  professor->teach();
              }
          }
      };
      
      int main() {
          Professor prof1, prof2;
          Department dept;
      
          dept.addProfessor(&prof1);
          dept.addProfessor(&prof2);
          
          dept.showProfessors();
      
          return 0;
      }

- **Composition**: A stronger "has-a" relationship where contained objects depend on the container.

      #include <iostream>
      using namespace std;
      
      // Room class
      class Room {
      public:
          Room() {
              cout << "Room created." << endl;
          }
          ~Room() {
              cout << "Room destroyed." << endl;
          }
      
          void describe() {
              cout << "This is a room." << endl;
          }
      };
      
      // House class (composed of Rooms)
      class House {
      private:
          Room room;  // House "owns" the Room (composition)
      
      public:
          void showRoom() {
              room.describe();
          }
      };
      
      int main() {
          House house;
          house.showRoom();  // Display room description
      
          // The Room object is destroyed when the House object goes out of scope
          return 0;
      }

## 24. Object-Oriented Design Principles
- Encapsulation
- Abstraction
- Polymorphism
- Inheritance
- Composition
- SOLID Principles
- Keep It Simple Stupid (KISS)
- Don't Repeat Yourself (DRY)

## 25. Operator Overloading
- Redefining the behavior of operators for user-defined types.

      #include <iostream>
      #include <cstdlib>
      
      void* operator new(size_t size) {
          std::cout << "Custom new called! Allocating " << size << " bytes." << std::endl;
          void* p = std::malloc(size);
          if (!p) {
              throw std::bad_alloc();  // If memory allocation fails
          }
          return p;
      }
      
      void operator delete(void* p) noexcept {
          std::cout << "Custom delete called!" << std::endl;
          std::free(p);
      }
      
      class MyClass {
      public:
          MyClass() {
              std::cout << "MyClass constructor" << std::endl;
          }
          ~MyClass() {
              std::cout << "MyClass destructor" << std::endl;
          }
      };
      
      int main() {
          // Using custom new and delete
          MyClass* obj = new MyClass();  // Calls overloaded new
          delete obj;                    // Calls overloaded delete
          return 0;
      }

## 26. Overloading
- Providing multiple methods with the same name but different parameters or types.

## 27. Polymorphism
The ability to process objects differently based on their data type or class, commonly achieved through method overriding and overloading.
- Compile Time Polymorphism:

      #include <iostream>
      using namespace std;
      
      // Function overloading: Same function name, different parameters
      void display(int i) {
          cout << "Integer: " << i << endl;
      }
      
      void display(double d) {
          cout << "Double: " << d << endl;
      }
      
      int main() {
          display(10);    // Calls the integer version
          display(5.5);   // Calls the double version
          return 0;
      }

- Runtime Polymorphism:

      #include <iostream>
      using namespace std;
      
      // Base class
      class Shape {
      public:
          virtual void draw() {  // Virtual function
              cout << "Drawing a Shape" << endl;
          }
      };
      
      // Derived class 1
      class Circle : public Shape {
      public:
          void draw() override {  // Override base class function
              cout << "Drawing a Circle" << endl;
          }
      };
      
      // Derived class 2
      class Rectangle : public Shape {
      public:
          void draw() override {  // Override base class function
              cout << "Drawing a Rectangle" << endl;
          }
      };
      
      int main() {
          Shape* shapePtr;
          Circle circle;
          Rectangle rectangle;
      
          // Using the base class pointer to refer to derived class objects
          shapePtr = &circle;
          shapePtr->draw();  // Calls Circle's draw()
      
          shapePtr = &rectangle;
          shapePtr->draw();  // Calls Rectangle's draw()
      
          return 0;
      }

## 28. SOLID Principles
Principles for maintainable OOP design.
- **S**ingle Responsibility
- **O**pen/Closed
- **L**iskov Substitution
- **I**nterface Segregation
- **D**ependency Inversion

## 29. Static (Methods and Variables)
- **Static Variables**: Shared among all class instances.
- **Static Methods**: Methods that belong to the class rather than any instance.

## 30. Testing in OOP
- **Unit Testing**: Testing individual components of code.
- **Test-Driven Development**: Writing tests before implementing functionality.

## 31. UML Diagrams and Modeling
- Unified Modeling Language diagrams like class, sequence, and activity diagrams to design and visualize OOP systems.

## 32. Virtual
- A keyword in languages like C++ to enable method overriding in derived classes, supporting runtime polymorphism.
