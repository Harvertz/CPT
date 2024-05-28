#include <limits>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <algorithm>

class Material {
public:
    int materialID;
    std::string name;
    double price;
    int quantity;
    int warningThreshold;

    Material(int id, std::string n, double p, int q, int wt)
        : materialID(id), name(n), price(p), quantity(q), warningThreshold(wt) {}

    void display() {
        std::cout << "Material ID: " << materialID << ", Name: " << name
            << ", Price: " << price << ", Quantity: " << quantity
            << ", Warning Threshold: " << warningThreshold << std::endl;
    }
};

class Dish {
public:
    int dishID;
    std::string name;
    double price;
    std::string category;
    std::vector<Material> ingredients;

    Dish(int id, std::string n, double p, std::string c, std::vector<Material> ing)
        : dishID(id), name(n), price(p), category(c), ingredients(ing) {}

    void display() {
        std::cout << "Dish ID: " << dishID << ", Name: " << name
            << ", Price: " << price << ", Category: " << category << std::endl;
        std::cout << "Ingredients: " << std::endl;
        for (auto& ingredient : ingredients) {
            ingredient.display();
        }
    }
};

class User {
public:
    int userID;
    std::string username;
    std::string password;
    std::string role; // Admin, Chef, Customer

    User(int id, std::string u, std::string p, std::string r)
        : userID(id), username(u), password(p), role(r) {}

    bool login(std::string uname, std::string pwd) {
        return username == uname && password == pwd;
    }

    std::string getRole() {
        return role;
    }

    void display() {
        std::cout << "User ID: " << userID << ", Username: " << username
            << ", Role: " << role << std::endl;
    }
};

class Customer {
public:
    int customerID;
    std::string name;
    std::string contact;
    int points;
    std::string discountInfo;

    Customer(int id, std::string n, std::string c, int p, std::string d)
        : customerID(id), name(n), contact(c), points(p), discountInfo(d) {}

    void display() {
        std::cout << "Customer ID: " << customerID << ", Name: " << name
            << ", Contact: " << contact << ", Points: " << points
            << ", Discount Info: " << discountInfo << std::endl;
    }
};

class Order {
public:
    int orderID;
    int customerID;
    std::vector<Dish> dishes;
    double totalFee;
    std::string status; // New, In Preparation, Completed
    std::string paymentMethod;

    Order(int id, int cid, std::vector<Dish> d, std::string pm)
        : orderID(id), customerID(cid), dishes(d), paymentMethod(pm), status("New") {
        totalFee = calculateTotalFee();
    }

    double calculateTotalFee() {
        double total = 0;
        for (auto& dish : dishes) {
            total += dish.price;
        }
        return total;
    }

    void updateStatus(std::string newStatus) {
        status = newStatus;
    }

    void display() {
        std::cout << "Order ID: " << orderID << ", Customer ID: " << customerID
            << ", Total Fee: " << totalFee << ", Status: " << status
            << ", Payment Method: " << paymentMethod << std::endl;
        std::cout << "Dishes: " << std::endl;
        for (auto& dish : dishes) {
            dish.display();
        }
    }
    void display2() {
        std::cout << "Total Fee: " << totalFee << std::endl;
    }
};

class Notification {
public:
    int notificationID;
    std::string type; // Stock Warning, Order Notification
    std::string content;
    std::string time;

    Notification(int id, std::string t, std::string c, std::string tm)
        : notificationID(id), type(t), content(c), time(tm) {}

    void display() {
        std::cout << "Notification ID: " << notificationID << ", Type: " << type
            << ", Content: " << content << ", Time: " << time << std::endl;
    }
};

class Finance {
public:
    double totalIncome;
    double totalCost;
    double grossProfit;

    Finance() : totalIncome(0), totalCost(0), grossProfit(0) {}

    void calculateFinance(std::vector<Order> orders, std::vector<Material> materials) {
        totalIncome = 0;
        for (auto& order : orders) {
            totalIncome += order.totalFee;
        }
        totalCost = 0;
        for (auto& material : materials) {
            totalCost += material.price * material.quantity;
        }
        grossProfit = totalIncome - totalCost;
    }

    void display() {
        std::cout << "Total Income: " << totalIncome << ", Total Cost: " << totalCost
            << ", Gross Profit: " << grossProfit << std::endl;
    }
};

class RestaurantManagementSystem {
private:
    std::vector<User> users;
    std::vector<Material> materials;
    std::vector<Dish> dishes;
    std::vector<Customer> customers;
    std::vector<Order> orders;
    std::vector<Notification> notifications;
    Finance finance;

    User* loggedInUser = nullptr;

public:
    bool login(std::string username, std::string password) {
        for (auto& user : users) {
            if (user.login(username, password)) {
                loggedInUser = &user;
                return true;
            }
        }
        return false;
    }

    void registerUser(User user) {
        if (std::find_if(users.begin(), users.end(), [&](const User& u) { return u.userID == user.userID; }) != users.end()) {
            std::cout << "User ID already exists. Please try again.\n";
            return;
        }
        users.push_back(user);
        std::cout << "User registered successfully.\n";
    }

    void addUser(User user) {
        if (loggedInUser == nullptr || loggedInUser->getRole() != "Admin") {
            std::cout << "Permission denied.\n";
            return;
        }
        if (std::find_if(users.begin(), users.end(), [&](const User& u) { return u.userID == user.userID; }) != users.end()) {
            std::cout << "User ID already exists. Returning to main menu.\n";
            return;
        }
        
            users.push_back(user);
            std::cout << "User added successfully.\n";
        
    }

    void addMaterial(Material material) {
        if (loggedInUser == nullptr || loggedInUser->getRole() != "Admin") {
            std::cout << "Permission denied.\n";
            return;
        }
        if (std::find_if(materials.begin(), materials.end(), [&](const Material& m) { return m.materialID == material.materialID; }) != materials.end()) {
            std::cout << "Material ID already exists. Returning to main menu.\n";
            return;
        }
       
            materials.push_back(material);
            std::cout << "Material added successfully.\n";
    }

    void addDish(Dish dish) {
        if (loggedInUser == nullptr || (loggedInUser->getRole() != "Admin" && loggedInUser->getRole() != "Chef")) {
            std::cout << "Permission denied.\n";
            return;
        }
        if (std::find_if(dishes.begin(), dishes.end(), [&](const Dish& d) { return d.dishID == dish.dishID || d.name == dish.name; }) != dishes.end()) {
            std::cout << "Dish ID or Name already exists. Returning to main menu.\n";
            return;
        }
        
            dishes.push_back(dish);
            std::cout << "Dish added successfully.\n";
    }

    void addCustomer(Customer customer) {
        if (loggedInUser == nullptr || loggedInUser->getRole() != "Admin") {
            std::cout << "Permission denied.\n";
            return;
        }
        if (std::find_if(customers.begin(), customers.end(), [&](const Customer& c) { return c.customerID == customer.customerID; }) != customers.end()) {
            std::cout << "Customer ID already exists. Returning to main menu.\n";
            return;
        }
        
            customers.push_back(customer);
            std::cout << "Customer added successfully.\n";
    }

    void addOrder(Order order) {
        if (loggedInUser == nullptr || loggedInUser->getRole() != "Customer") {
            std::cout << "Permission denied.\n";
            return;
        }
        if (std::find_if(orders.begin(), orders.end(), [&](const Order& o) { return o.orderID == order.orderID; }) != orders.end()) {
            std::cout << "Order ID already exists. Returning to main menu.\n";
            return;
        }
        
            orders.push_back(order);
            std::cout << "Order added successfully.\n";
    }

    void addNotification(Notification notification) {
        if (loggedInUser == nullptr || loggedInUser->getRole() != "Admin") {
            std::cout << "Permission denied.\n";
            return;
        }
        if (std::find_if(notifications.begin(), notifications.end(), [&](const Notification& n) { return n.notificationID == notification.notificationID; }) != notifications.end()) {
            std::cout << "Notification ID already exists. Returning to main menu.\n";
            return;
        }
        
            notifications.push_back(notification);
            std::cout << "Notification added successfully.\n";
    }

    void displayUsers() {
        if (loggedInUser == nullptr || loggedInUser->getRole() != "Admin") {
            std::cout << "Permission denied.\n";
            return;
        }
        if (users.empty()) {
            std::cout << "No users available.\n";
        }
        else {
            for (auto& user : users) {
                user.display();
            }
        }
    }

    void displayMaterials() {
        if (loggedInUser == nullptr || (loggedInUser->getRole() != "Admin" && loggedInUser->getRole() != "Chef")) {
            std::cout << "Permission denied.\n";
            return;
        }
        if (materials.empty()) {
            std::cout << "No materials available.\n";
        }
        else {
            for (auto& material : materials) {
                material.display();
            }
        }
    }

    void displayDishes() {
        if (dishes.empty()) {
            std::cout << "No dishes available.\n";
        }
        else {
            for (auto& dish : dishes) {
                dish.display();
            }
        }
    }

    void displayCustomers() {
        if (loggedInUser == nullptr || loggedInUser->getRole() != "Admin") {
            std::cout << "Permission denied.\n";
            return;
        }
        if (customers.empty()) {
            std::cout << "No customers available.\n";
        }
        else {
            for (auto& customer : customers) {
                customer.display();
            }
        }
    }

    void displayOrders() {
        if (loggedInUser == nullptr || loggedInUser->getRole() != "Admin") {
            std::cout << "Permission denied.\n";
            return;
        }
        if (orders.empty()) {
            std::cout << "No orders available.\n";
        }
        else {
            for (auto& order : orders) {
                order.display();
            }
        }
    }

    void displayTotalFee() {
        if (loggedInUser == nullptr || loggedInUser->getRole() != "Cusotmer") 
        {
            std::cout << "Permission denied.\n";
            return;
        }
        if (orders.empty()) {
            std::cout << "No orders available.\n";
        }
        else {
            for (auto& order : orders) {
                order.display2();
            }
        }
    }

    void displayNotifications() {
        if (loggedInUser == nullptr || loggedInUser->getRole() != "Admin") {
            std::cout << "Permission denied.\n";
            return;
        }
        if (notifications.empty()) {
            std::cout << "No notifications available.\n";
        }
        else {
            for (auto& notification : notifications) {
                notification.display();
            }
        }
    }

    void calculateFinance() {
        if (loggedInUser == nullptr || loggedInUser->getRole() != "Admin") {
            std::cout << "Permission denied.\n";
            return;
        }
        if (orders.empty() || materials.empty()) {
            std::cout << "Not enough data to calculate finance.\n";
        }
        else {
            finance.calculateFinance(orders, materials);
            finance.display();
        }
    }
    

    Material getMaterialByID(int id) {
        for (auto& material : materials) {
            if (material.materialID == id) {
                return material;
            }
        }
        throw std::runtime_error("Material not found");
    }

    Dish getDishByID(int id) {
        for (auto& dish : dishes) {
            if (dish.dishID == id) {
                return dish;
            }
        }
        throw std::runtime_error("Dish not found");
    }

    void modifyUser(int userID) {
        if (loggedInUser == nullptr || loggedInUser->getRole() != "Admin") {
            std::cout << "Permission denied.\n";
            return;
        }
        auto it = std::find_if(users.begin(), users.end(), [&](const User& u) { return u.userID == userID; });
        if (it == users.end()) {
            std::cout << "User ID not found. Returning to main menu.\n";
            return;
        }
        std::string username, password, role;
        std::cout << "Enter new Username: ";
        std::cin >> username;
        std::cout << "Enter new Password: ";
        std::cin >> password;
        std::cout << "Enter new Role (Admin/Chef/Customer): ";
        std::cin >> role;
        if (role != "Admin" && role != "Chef" && role != "Customer") {
            std::cout << "Invalid Role. Returning to main menu.\n";
            return;
        }
        it->username = username;
        it->password = password;
        it->role = role;
        std::cout << "User modified successfully.\n";
    }

    void modifyMaterial(int materialID) {
        if (loggedInUser == nullptr || loggedInUser->getRole() != "Admin") {
            std::cout << "Permission denied.\n";
            return;
        }
        auto it = std::find_if(materials.begin(), materials.end(), [&](const Material& m) { return m.materialID == materialID; });
        if (it == materials.end()) {
            std::cout << "Material ID not found. Returning to main menu.\n";
            return;
        }
        std::string name;
        double price;
        int quantity, warningThreshold;
        std::cout << "Enter new Material Name: ";
        std::cin >> name;
        std::cout << "Enter new Material Price: ";
        std::cin >> price;
        std::cout << "Enter new Quantity: ";
        std::cin >> quantity;
        std::cout << "Enter new Warning Threshold: ";
        std::cin >> warningThreshold;
        it->name = name;
        it->price = price;
        it->quantity = quantity;
        it->warningThreshold = warningThreshold;
        std::cout << "Material modified successfully.\n";
    }

    void modifyDish(int dishID) {
        if (loggedInUser == nullptr || (loggedInUser->getRole() != "Admin" && loggedInUser->getRole() != "Chef")) {
            std::cout << "Permission denied.\n";
            return;
        }
        auto it = std::find_if(dishes.begin(), dishes.end(), [&](const Dish& d) { return d.dishID == dishID; });
        if (it == dishes.end()) {
            std::cout << "Dish ID not found. Returning to main menu.\n";
            return;
        }
        std::string name, category;
        double price;
        int numIngredients;
        std::cout << "Enter new Dish Name: ";
        std::cin >> name;
        std::cout << "Enter new Dish Price: ";
        std::cin >> price;
        std::cout << "Enter new Dish Category: ";
        std::cin >> category;
        std::cout << "Enter number of new ingredients: ";
        std::cin >> numIngredients;
        std::vector<Material> ingredients;
        for (int i = 0; i < numIngredients; ++i) {
            int materialID;
            std::cout << "Enter Material ID for ingredient " << (i + 1) << ": ";
            std::cin >> materialID;
            try {
                ingredients.push_back(getMaterialByID(materialID));
            }
            catch (const std::runtime_error& e) {
                std::cout << e.what() << std::endl;
                --i; // Retry this ingredient
            }
        }
        it->name = name;
        it->price = price;
        it->category = category;
        it->ingredients = ingredients;
        std::cout << "Dish modified successfully.\n";
    }

    void modifyCustomer(int customerID) {
        if (loggedInUser == nullptr || loggedInUser->getRole() != "Admin") {
            std::cout << "Permission denied.\n";
            return;
        }
        auto it = std::find_if(customers.begin(), customers.end(), [&](const Customer& c) { return c.customerID == customerID; });
        if (it == customers.end()) {
            std::cout << "Customer ID not found. Returning to main menu.\n";
            return;
        }
        std::string name, contact, discountInfo;
        int points;
        std::cout << "Enter new Customer Name: ";
        std::cin >> name;
        std::cout << "Enter new Contact: ";
        std::cin >> contact;
        std::cout << "Enter new Points: ";
        std::cin >> points;
        std::cout << "Enter new Discount Info: ";
        std::cin >> discountInfo;
        it->name = name;
        it->contact = contact;
        it->points = points;
        it->discountInfo = discountInfo;
        std::cout << "Customer modified successfully.\n";
    }

    void modifyOrder(int orderID) {
        if (loggedInUser == nullptr || loggedInUser->getRole() != "Admin") {
            std::cout << "Permission denied.\n";
            return;
        }
        auto it = std::find_if(orders.begin(), orders.end(), [&](const Order& o) { return o.orderID == orderID; });
        if (it == orders.end()) {
            std::cout << "Order ID not found. Returning to main menu.\n";
            return;
        }
        int customerID, numDishes;
        std::string paymentMethod;
        std::cout << "Enter new Customer ID: ";
        std::cin >> customerID;
        std::cout << "Enter number of new dishes: ";
        std::cin >> numDishes;
        std::vector<Dish> dishes;
        for (int i = 0; i < numDishes; ++i) {
            int dishID;
            std::cout << "Enter Dish ID for dish " << (i + 1) << ": ";
            std::cin >> dishID;
            try {
                dishes.push_back(getDishByID(dishID));
            }
            catch (const std::runtime_error& e) {
                std::cout << e.what() << std::endl;
                --i; // Retry this dish
            }
        }
        std::cout << "Enter new Payment Method: ";
        std::cin >> paymentMethod;
        it->customerID = customerID;
        it->dishes = dishes;
        it->paymentMethod = paymentMethod;
        it->totalFee = it->calculateTotalFee();
        std::cout << "Order modified successfully.\n";
    }

    void modifyNotification(int notificationID) {
        if (loggedInUser == nullptr || loggedInUser->getRole() != "Admin") {
            std::cout << "Permission denied.\n";
            return;
        }
        auto it = std::find_if(notifications.begin(), notifications.end(), [&](const Notification& n) { return n.notificationID == notificationID; });
        if (it == notifications.end()) {
            std::cout << "Notification ID not found. Returning to main menu.\n";
            return;
        }
        std::string type, content, time;
        std::cout << "Enter new Notification Type: ";
        std::cin >> type;
        std::cout << "Enter new Notification Content: ";
        std::cin >> content;
        std::cout << "Enter new Notification Time: ";
        std::cin >> time;
        it->type = type;
        it->content = content;
        it->time = time;
        std::cout << "Notification modified successfully.\n";
    }

    void deleteUser(int userID) {
        if (loggedInUser == nullptr || loggedInUser->getRole() != "Admin") {
            std::cout << "Permission denied.\n";
            return;
        }
        auto it = std::remove_if(users.begin(), users.end(), [&](const User& u) { return u.userID == userID; });
        if (it == users.end()) {
            std::cout << "User ID not found. Returning to main menu.\n";
            return;
        }
        users.erase(it, users.end());
        std::cout << "User deleted successfully.\n";
    }

    void deleteMaterial(int materialID) {
        if (loggedInUser == nullptr || loggedInUser->getRole() != "Admin") {
            std::cout << "Permission denied.\n";
            return;
        }
        auto it = std::remove_if(materials.begin(), materials.end(), [&](const Material& m) { return m.materialID == materialID; });
        if (it == materials.end()) {
            std::cout << "Material ID not found. Returning to main menu.\n";
            return;
        }
        materials.erase(it, materials.end());
        std::cout << "Material deleted successfully.\n";
    }

    void deleteDish(int dishID) {
        if (loggedInUser == nullptr || (loggedInUser->getRole() != "Admin" && loggedInUser->getRole() != "Chef")) {
            std::cout << "Permission denied.\n";
            return;
        }
        auto it = std::remove_if(dishes.begin(), dishes.end(), [&](const Dish& d) { return d.dishID == dishID; });
        if (it == dishes.end()) {
            std::cout << "Dish ID not found. Returning to main menu.\n";
            return;
        }
        dishes.erase(it, dishes.end());
        std::cout << "Dish deleted successfully.\n";
    }

    void deleteCustomer(int customerID) {
        if (loggedInUser == nullptr || loggedInUser->getRole() != "Admin") {
            std::cout << "Permission denied.\n";
            return;
        }
        auto it = std::remove_if(customers.begin(), customers.end(), [&](const Customer& c) { return c.customerID == customerID; });
        if (it == customers.end()) {
            std::cout << "Customer ID not found. Returning to main menu.\n";
            return;
        }
        customers.erase(it, customers.end());
        std::cout << "Customer deleted successfully.\n";
    }

    void deleteOrder(int orderID) {
        if (loggedInUser == nullptr || loggedInUser->getRole() != "Admin") {
            std::cout << "Permission denied.\n";
            return;
        }
        auto it = std::remove_if(orders.begin(), orders.end(), [&](const Order& o) { return o.orderID == orderID; });
        if (it == orders.end()) {
            std::cout << "Order ID not found. Returning to main menu.\n";
            return;
        }
        orders.erase(it, orders.end());
        std::cout << "Order deleted successfully.\n";
    }

    void deleteNotification(int notificationID) {
        if (loggedInUser == nullptr || loggedInUser->getRole() != "Admin") {
            std::cout << "Permission denied.\n";
            return;
        }
        auto it = std::remove_if(notifications.begin(), notifications.end(), [&](const Notification& n) { return n.notificationID == notificationID; });
        if (it == notifications.end()) {
            std::cout << "Notification ID not found. Returning to main menu.\n";
            return;
        }
        notifications.erase(it, notifications.end());
        std::cout << "Notification deleted successfully.\n";
    }
};

int main() {
    RestaurantManagementSystem rms;
    int choice;

    do {
        std::cout << "\n************************************\n";
        std::cout << "1. Register\n";
        std::cout << "2. Login\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore bad input
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
        case 1: {
            int id;
            std::string username, password, role;
            std::cout << "Enter User ID: ";
            std::cin >> id;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid User ID. Returning to main menu.\n";
                break;
            }
            std::cout << "Enter Username: ";
            std::cin >> username;
            std::cout << "Enter Password: ";
            std::cin >> password;
            std::cout << "Enter Role (Admin/Chef/Customer): ";
            std::cin >> role;
            if (role != "Admin" && role != "Chef" && role != "Customer") {
                std::cout << "Invalid Role. Returning to main menu.\n";
                break;
            }
            rms.registerUser(User(id, username, password, role));
            break;
        }
        case 2: {
            std::string username, password;
            std::cout << "Enter Username: ";
            std::cin >> username;
            std::cout << "Enter Password: ";
            std::cin >> password;
            if (rms.login(username, password)) {
                int userChoice;
                do {
                    std::cout << "\n************************************\n";
                    std::cout << "Restaurant Management System\n";
                    std::cout << "1. Add\n";
                    std::cout << "2. Modify\n";
                    std::cout << "3. Delete\n";
                    std::cout << "4. Display\n";
                    std::cout << "5. Calculate Finance\n";
                    std::cout << "6. Check out\n";
                    std::cout << "0. Logout\n";
                    std::cout << "Enter your choice: ";
                    std::cin >> userChoice;

                    if (std::cin.fail()) {
                        std::cin.clear(); // Clear error flags
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore bad input
                        std::cout << "Invalid input. Please enter a number.\n";
                        continue;
                    }

                    switch (userChoice) {
                    case 1: {
                        int addChoice;
                        std::cout << "\nAdd Menu\n";
                        std::cout << "1. Add User\n";
                        std::cout << "2. Add Material\n";
                        std::cout << "3. Add Dish\n";
                        std::cout << "4. Add Customer\n";
                        std::cout << "5. Add Order\n";
                        std::cout << "6. Add Notification\n";
                        std::cout << "0. Back\n";
                        std::cout << "Enter your choice: ";
                        std::cin >> addChoice;

                        switch (addChoice) {
                        case 1: {
                            int id;
                            std::string username, password, role;
                            std::cout << "Enter User ID: ";
                            std::cin >> id;
                            if (std::cin.fail()) {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                std::cout << "Invalid User ID. Returning to add menu.\n";
                                break;
                            }
                            std::cout << "Enter Username: ";
                            std::cin >> username;
                            std::cout << "Enter Password: ";
                            std::cin >> password;
                            std::cout << "Enter Role (Admin/Chef/Customer): ";
                            std::cin >> role;
                            if (role != "Admin" && role != "Chef" && role != "Customer") {
                                std::cout << "Invalid Role. Returning to add menu.\n";
                                break;
                            }
                            rms.addUser(User(id, username, password, role));
                            break;
                        }
                        case 2: {
                            int id, quantity, warningThreshold;
                            std::string name;
                            double price;
                            std::cout << "Enter Material ID: ";
                            std::cin >> id;
                            if (std::cin.fail()) {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                std::cout << "Invalid Material ID. Returning to add menu.\n";
                                break;
                            }
                            std::cout << "Enter Material Name: ";
                            std::cin >> name;
                            std::cout << "Enter Material Price: ";
                            std::cin >> price;
                            if (std::cin.fail()) {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                std::cout << "Invalid Material Price. Returning to add menu.\n";
                                break;
                            }
                            std::cout << "Enter Quantity: ";
                            std::cin >> quantity;
                            if (std::cin.fail()) {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                std::cout << "Invalid Quantity. Returning to add menu.\n";
                                break;
                            }
                            std::cout << "Enter Warning Threshold: ";
                            std::cin >> warningThreshold;
                            if (std::cin.fail()) {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                std::cout << "Invalid Warning Threshold. Returning to add menu.\n";
                                break;
                            }
                            rms.addMaterial(Material(id, name, price, quantity, warningThreshold));
                            
                            break;
                        }
                        case 3: {
             
                            int id, numIngredients;
                            std::string name, category;
                            double price;
                            std::cout << "Enter Dish ID: ";
                            std::cin >> id;
                            if (std::cin.fail()) {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                std::cout << "Invalid Dish ID. Returning to add menu.\n";
                                break;
                            }
                            std::cout << "Enter Dish Name: ";
                            std::cin >> name;
                            std::cout << "Enter Dish Price: ";
                            std::cin >> price;
                            if (std::cin.fail()) {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                std::cout << "Invalid Dish Price. Returning to add menu.\n";
                                break;
                            }
                            std::cout << "Enter Dish Category: ";
                            std::cin >> category;
                            std::cout << "Enter number of ingredients: ";
                            std::cin >> numIngredients;
                            if (std::cin.fail()) {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                std::cout << "Invalid number of ingredients. Returning to add menu.\n";
                                break;
                            }
                            std::vector<Material> ingredients;
                            for (int i = 0; i < numIngredients; ++i) {
                                int materialID;
                                std::cout << "Enter Material ID for ingredient " << (i + 1) << "(enter any letters to break the loop if you didn't add any materials frist): ";
                                std::cin >> materialID;
                                if (std::cin.fail()) {
                                    std::cin.clear();
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                    std::cout << "Invalid Material ID. Returning to add menu.\n";
                                    ingredients.clear();
                                    break;
                                }
                                try {
                                    ingredients.push_back(rms.getMaterialByID(materialID));
                                }
                                catch (const std::runtime_error& e) {
                                    std::cout << e.what() << std::endl;
                                    --i; // Retry this ingredient
                                }
                            }
                            if (!ingredients.empty()) {
                                rms.addDish(Dish(id, name, price, category, ingredients));
                            }
                            break;
                        }
                        case 4: {
                            int id, points;
                            std::string name, contact, discountInfo;
                            std::cout << "Enter Customer ID: ";
                            std::cin >> id;
                            if (std::cin.fail()) {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                std::cout << "Invalid Customer ID. Returning to add menu.\n";
                                break;
                            }
                            std::cout << "Enter Customer Name: ";
                            std::cin >> name;
                            std::cout << "Enter Contact: ";
                            std::cin >> contact;
                            std::cout << "Enter Points: ";
                            std::cin >> points;
                            if (std::cin.fail()) {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                std::cout << "Invalid Points. Returning to add menu.\n";
                                break;
                            }
                            std::cout << "Enter Discount Info: ";
                            std::cin >> discountInfo;
                            rms.addCustomer(Customer(id, name, contact, points, discountInfo));
                            break;
                        }
                        case 5: {
                            int id, customerID, numDishes;
                            std::string paymentMethod;
                            std::cout << "Enter Order ID: ";
                            std::cin >> id;
                            if (std::cin.fail()) {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                std::cout << "Invalid Order ID. Returning to add menu.\n";
                                break;
                            }
                            std::cout << "Enter Customer ID: ";
                            std::cin >> customerID;
                            if (std::cin.fail()) {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                std::cout << "Invalid Customer ID. Returning to add menu.\n";
                                break;
                            }
                            std::cout << "Enter number of dishes: ";
                            std::cin >> numDishes;
                            if (std::cin.fail()) {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                std::cout << "Invalid number of dishes. Returning to add menu.\n";
                                break;
                            }
                            std::vector<Dish> dishes;
                            for (int i = 0; i < numDishes; ++i) {
                                int dishID;
                                std::cout << "Enter Dish ID for dish " << (i + 1) << ": ";
                                std::cin >> dishID;
                                if (std::cin.fail()) {
                                    std::cin.clear();
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                    std::cout << "Invalid Dish ID. Returning to add menu.\n";
                                    dishes.clear();
                                    break;
                                }
                                try {
                                    dishes.push_back(rms.getDishByID(dishID));
                                }
                                catch (const std::runtime_error& e) {
                                    std::cout << e.what() << std::endl;
                                    --i; // Retry this dish
                                }
                            }
                            if (!dishes.empty()) {
                                std::cout << "Enter Payment Method: ";
                                std::cin >> paymentMethod;
                                rms.addOrder(Order(id, customerID, dishes, paymentMethod));
                               
                            }
                            break;
                        }
                        case 6: {
                            int id;
                            std::string type, content, time;
                            std::cout << "Enter Notification ID: ";
                            std::cin >> id;
                            if (std::cin.fail()) {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                std::cout << "Invalid Notification ID. Returning to add menu.\n";
                                break;
                            }
                            std::cout << "Enter Notification Type: ";
                            std::cin >> type;
                            std::cout << "Enter Notification Content: ";
                            std::cin >> content;
                            std::cout << "Enter Notification Time: ";
                            std::cin >> time;
                            rms.addNotification(Notification(id, type, content, time));
                            
                            break;
                        }
                        case 0:
                            std::cout << "Returning to add menu.\n";
                            break;
                        default:
                            std::cout << "Invalid choice, returning to main menu.\n";
                        }
                        break;
                    }
                    case 2: {
                        int modifyChoice;
                        std::cout << "\nModify Menu\n";
                        std::cout << "1. Modify User\n";
                        std::cout << "2. Modify Material\n";
                        std::cout << "3. Modify Dish\n";
                        std::cout << "4. Modify Customer\n";
                        std::cout << "5. Modify Order\n";
                        std::cout << "6. Modify Notification\n";
                        std::cout << "0. Back\n";
                        std::cout << "Enter your choice: ";
                        std::cin >> modifyChoice;

                        switch (modifyChoice) {
                        case 1: {
                            int userID;
                            std::cout << "Enter User ID to modify: ";
                            std::cin >> userID;
                            rms.modifyUser(userID);
                            break;
                        }
                        case 2: {
                            int materialID;
                            std::cout << "Enter Material ID to modify: ";
                            std::cin >> materialID;
                            rms.modifyMaterial(materialID);
                            break;
                        }
                        case 3: {
                            int dishID;
                            std::cout << "Enter Dish ID to modify: ";
                            std::cin >> dishID;
                            rms.modifyDish(dishID);
                            break;
                        }
                        case 4: {
                            int customerID;
                            std::cout << "Enter Customer ID to modify: ";
                            std::cin >> customerID;
                            rms.modifyCustomer(customerID);
                            break;
                        }
                        case 5: {
                            int orderID;
                            std::cout << "Enter Order ID to modify: ";
                            std::cin >> orderID;
                            rms.modifyOrder(orderID);
                            break;
                        }
                        case 6: {
                            int notificationID;
                            std::cout << "Enter Notification ID to modify: ";
                            std::cin >> notificationID;
                            rms.modifyNotification(notificationID);
                            break;
                        }
                        case 0:
                            std::cout << "Returning to modify menu.\n";
                            break;
                        default:
                            std::cout << "Invalid choice, returning to main menu.\n";
                        }
                        break;
                    }
                    case 3: {
                        int deleteChoice;
                        std::cout << "\nDelete Menu\n";
                        std::cout << "1. Delete User\n";
                        std::cout << "2. Delete Material\n";
                        std::cout << "3. Delete Dish\n";
                        std::cout << "4. Delete Customer\n";
                        std::cout << "5. Delete Order\n";
                        std::cout << "6. Delete Notification\n";
                        std::cout << "0. Back\n";
                        std::cout << "Enter your choice: ";
                        std::cin >> deleteChoice;

                        switch (deleteChoice) {
                        case 1: {
                            int userID;
                            std::cout << "Enter User ID to delete: ";
                            std::cin >> userID;
                            rms.deleteUser(userID);
                            break;
                        }
                        case 2: {
                            int materialID;
                            std::cout << "Enter Material ID to delete: ";
                            std::cin >> materialID;
                            rms.deleteMaterial(materialID);
                            break;
                        }
                        case 3: {
                            int dishID;
                            std::cout << "Enter Dish ID to delete: ";
                            std::cin >> dishID;
                            rms.deleteDish(dishID);
                            break;
                        }
                        case 4: {
                            int customerID;
                            std::cout << "Enter Customer ID to delete: ";
                            std::cin >> customerID;
                            rms.deleteCustomer(customerID);
                            break;
                        }
                        case 5: {
                            int orderID;
                            std::cout << "Enter Order ID to delete: ";
                            std::cin >> orderID;
                            rms.deleteOrder(orderID);
                            break;
                        }
                        case 6: {
                            int notificationID;
                            std::cout << "Enter Notification ID to delete: ";
                            std::cin >> notificationID;
                            rms.deleteNotification(notificationID);
                            break;
                        }
                        case 0:
                            std::cout << "Returning to delete menu.\n";
                            break;
                        default:
                            std::cout << "Invalid choice, returning to main menu.\n";
                        }
                        break;
                    }
                    case 4: {
                        int displayChoice;
                        std::cout << "\nDisplay Menu\n";
                        std::cout << "1. Display Users\n";
                        std::cout << "2. Display Materials\n";
                        std::cout << "3. Display Dishes\n";
                        std::cout << "4. Display Customers\n";
                        std::cout << "5. Display Orders\n";
                        std::cout << "6. Display Notifications\n";
                        std::cout << "0. Back\n";
                        std::cout << "Enter your choice: ";
                        std::cin >> displayChoice;

                        switch (displayChoice) {
                        case 1:
                            rms.displayUsers();
                            break;
                        case 2:
                            rms.displayMaterials();
                            break;
                        case 3:
                            rms.displayDishes();
                            break;
                        case 4:
                            rms.displayCustomers();
                            break;
                        case 5:
                            rms.displayOrders();
                            break;
                        case 6:
                            rms.displayNotifications();
                            break;
                        case 0:
                            std::cout << "Returning to display menu.\n";
                            break;
                        default:
                            std::cout << "Invalid choice, returning to main menu.\n";
                        }
                        break;
                    }
                    case 5:
                        rms.calculateFinance();
                        break;
                    case 6:
                        rms.displayTotalFee();
                        break;
                    case 0:
                        std::cout << "Logging out.\n";
                        break;
                    default:
                        std::cout << "Invalid choice, please try again.\n";
                    }
                } while (userChoice != 0);
            }
            else {
                std::cout << "Invalid username or password. Please try again.\n";
            }
            break;
        }
        case 0:
            std::cout << "Exiting the system.\n";
            break;
        default:
            std::cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
