/*
* Title: project-1
* Abstract: This program will be an automat that will hold food items and drinks. A person can add food items or drinks to their order, and then either purchase or cancel the whole order.
* Author: Gabrielle Lake
* Email: glake@csumb.edu
* Estimate: 6 hours
* Date: 9/26/2020
*/

#include <iostream>
using namespace std;

const int AUTOMAT_MAX = 10;
const int ORDER_MAX = 5;

//Food Class
class Food
{
  public:
  Food();
  Food(string name, int calories, double price);
  string getName();
  int getCalories();
  double getPrice();
  void setName(string name);
  void setCalories(int calories);
  void setPrice(double price);
  void display();

  private:
  string myName;
  int myCalories;
  double myPrice;
};

//Drink Class
class Drink
{
  public:
  Drink();
  Drink(string name, int ounces, double price);
  string getName();
  int getOunces();
  double getPrice();
  void setName(string name);
  void setOunces(int ounces);
  void setPrice(double price);
  void display();

  private:
  string myName;
  int myOunces;
  double myPrice;
};

//Automat Class: Queue
class Automat
{
  public:
  Automat();
  bool emptyFood();
  bool emptyDrink();
  void enqueue(Food f);
  void enqueue(Drink d);
  void dequeueFood();
  void dequeueDrink();
  Food frontFood();
  Drink frontDrink();
  int foodCount();
  int drinkCount();
  int getTotalCalories();
  int getTotalOunces();
  double getTotalPrice();
  void display();

  private:
  int myFoodFront = 0;
  int myFoodBack = 0;
  int myDrinkFront = 0;
  int myDrinkBack = 0;
  Food myFood[AUTOMAT_MAX];
  Drink myDrink[AUTOMAT_MAX];

};

//Order Class: Stack
class Order
{
  public:
  Order();
  bool emptyFood();
  bool emptyDrink();
  void push(Food f);
  void push(Drink d);
  void popFood();
  void popDrink();
  Food topFood();
  Drink topDrink();
  int foodCount();
  int drinkCount();
  double getTotalPrice();
  void display();
  void cancel(Automat &);
  void purchase();
  static int getTotalOrders();

  private:
  int myFoodTop = -1;
  int myDrinkTop = -1;
  Food myFood[ORDER_MAX];
  Drink myDrink[ORDER_MAX];
  static int myTotalOrders;
};

//DEFINITIONS OF ALL FOOD CLASS FUNCTIONS:
  Food::Food()
  {
    myName = "DEFAULT NAME";
    myCalories = 0;
    myPrice = 0.0;
  }

  Food::Food(string name, int calories, double price)
  {
    myName = name;
    myCalories = calories;
    myPrice = price;
  }

  string Food::getName()
  {
    return myName;
  };

  int Food::getCalories()
  {
    return myCalories;
  }

  double Food::getPrice()
  {
    return myPrice;
  }

  void Food::setName(string name)
  {
    myName = name;
  }

  void Food::setCalories(int calories)
  {
    myCalories = calories;
  }

  void Food::setPrice(double price)
  {
    myPrice = price;
  }

  void Food::display()
  {
    cout << myName << ": " << myCalories << " calories, " << "$" << myPrice;
  }


//DEFINITIONS OF ALL DRINK CLASS FUNCTIONS:
  Drink::Drink()
  {
    myName = "DEFAULT NAME";
    myOunces = 0;
    myPrice = 0.0;
  }

  Drink::Drink(string name, int ounces, double price)
  {
    myName = name;
    myOunces = ounces;
    myPrice = price;
  }

  string Drink::getName()
  {
    return myName;
  }

  int Drink::getOunces()
  {
    return myOunces;
  }

  double Drink::getPrice()
  {
    return myPrice;
  }

  void Drink::setName(string name)
  {
    myName = name;
  }

  void Drink::setOunces(int ounces)
  {
    myOunces = ounces;
  }

  void Drink::setPrice(double price)
  {
    myPrice = price;
  }

  void Drink::display()
  {
    cout << myName << ": " << myOunces << " ounces, " << "$" << myPrice;
  }

//DEFINITIONS OF ALL AUTOMAT CLASS FUNCTIONS:
  Automat::Automat()
  {
    myFoodFront = 0;
    myFoodBack = 0;
    myDrinkFront = 0;
    myDrinkBack = 0;
  }

  bool Automat::emptyFood()
  {
    return (myFoodFront == myFoodBack);
  }

  bool Automat::emptyDrink()
  {
    return (myDrinkFront == myDrinkBack);
  }

  void Automat::enqueue(Food f)
  {
    int newFoodBack = (myFoodBack + 1)%AUTOMAT_MAX;
    if(newFoodBack != myFoodFront)
    {
      myFood[myFoodBack] = f;
      myFoodBack = newFoodBack;
    }
    else
    {
      cerr << "*** Automat food full; new food not added. ***" << endl;
    }
  }

  void Automat::enqueue(Drink d)
  {
    int newDrinkBack = (myDrinkBack + 1)%AUTOMAT_MAX;
    if(newDrinkBack != myDrinkFront)
    {
      myDrink[myDrinkBack] = d;
      myDrinkBack = newDrinkBack;
    }
    else
    {
      cerr << "*** Automat drink full; new drink not added. ***" << endl;
    }
  }

  void Automat::dequeueFood()
  {
    if(!emptyFood())
    {
      myFoodFront = (myFoodFront + 1)%AUTOMAT_MAX;
    }
    else
    {
      cerr << "*** Automat Food is empty -- can't remove food item ***" << endl;
    }
  }

  void Automat::dequeueDrink()
  {
    if(!emptyDrink())
    {
      myDrinkFront = (myDrinkFront + 1)%AUTOMAT_MAX;
    }
    else
    {
      cerr << "*** Automat Drink is empty -- can't remove drink ***";
    }
  }

  Food Automat::frontFood()
  {
    if(!emptyFood())
    {
      return myFood[myFoodFront];
    }
    else
    {
      cerr << "*** Automat Food is empty -- returning random value***";
      Food random;
      return random;
    }
  }

  Drink Automat::frontDrink()
  {
    if(!emptyDrink())
    {
      return myDrink[myDrinkFront];
    }
    else
    {
      cerr << "*** Automat Drink is empty -- returning random value ***";
      Drink random;
      return random;
    }
  }

  int Automat::foodCount()
  {
    int foodCount = 0;
    for(int i = myFoodFront; i != myFoodBack; i = (i + 1)%AUTOMAT_MAX)
    {
      if(myFood[i].getCalories() != 0)
      {
        foodCount++;
      }
    }
    return foodCount;
  }

  int Automat::drinkCount()
  {
    int drinkCount = 0;
    for(int i = myDrinkFront; i != myDrinkBack; i = (i + 1)%AUTOMAT_MAX)
    {
      if(myDrink[i].getOunces() != 0)
      {
        drinkCount++;
      }
    }
    return drinkCount;
  }
  
  int Automat::getTotalCalories()
  {
    int totalCalories = 0;
    for(int i = myFoodFront; i != myFoodBack; i = (i + 1)%AUTOMAT_MAX)
    {
      totalCalories += myFood[i].getCalories();
    }
    return totalCalories;
  }

  int Automat::getTotalOunces()
  {
    int totalOunces = 0;
    for(int i = myDrinkFront; i != myDrinkBack; i = (i + 1)%AUTOMAT_MAX)
    {
      totalOunces += myDrink[i].getOunces();
    }
    return totalOunces;
  }

  double Automat::getTotalPrice()
  {
    double totalPrice = 0;
    for(int i = myFoodFront; i != myFoodBack; i = (i + 1)%AUTOMAT_MAX)
    {
      totalPrice += myFood[i].getPrice();
    }
    for(int i = myDrinkFront; i != myDrinkBack; i = (i + 1)%AUTOMAT_MAX)
    {
      totalPrice += myDrink[i].getPrice();
    }
    return totalPrice;
  }

  void Automat::display()
  {
    cout << "Automat: " << endl << "\tFood: " << endl;
    for(int i = myFoodFront; i != myFoodBack; i = (i + 1)%AUTOMAT_MAX)
    {
      cout << "\t\t"; 
      myFood[i].display();
      cout << endl;
    }
    cout << "\t\t" << foodCount() << " food items - Total Calories: " << getTotalCalories() << endl;

    cout << "\tDrinks: " << endl;
    for(int i = myDrinkFront; i != myDrinkBack; i = (i + 1)%AUTOMAT_MAX)
    {
      cout << "\t\t"; 
      myDrink[i].display();
      cout << endl;
    }
    cout << "\t\t" << drinkCount() << " drinks -  Total Ounces: " << getTotalOunces() << endl << endl;
  }


//DEFINITIONS OF ALL ORDER CLASS FUNCTIONS:
  int Order::myTotalOrders = 0;

  Order::Order()
  {
    myFoodTop = -1;
    myDrinkTop = -1;
    myTotalOrders++;
  }

  bool Order::emptyFood()
  {
    return (myFoodTop == -1);
  }

  bool Order::emptyDrink()
  {
    return(myDrinkTop == -1);
  }

  void Order::push(Food f)
  {
    if(myFoodTop < ORDER_MAX - 1)
    {
      myFoodTop++;
      myFood[myFoodTop] = f;
    }
    else
    {
      cerr << "*** Order food is full -- new food not added ***";
    }
  }

  void Order::push(Drink d)
  {
    if(myDrinkTop < ORDER_MAX - 1)
    {
      myDrinkTop++;
      myDrink[myDrinkTop] = d;
    }
    else
    {
      cerr << "*** Order drink is full -- new drink not added ***";
    }
  }

  void Order::popFood()
  {
    if(!emptyFood())
    {
      myFoodTop--;
    }
    else
    {
      cerr << "*** Order food is empty -- can't remove food item ***" << endl;
    }
  }

  void Order::popDrink()
  {
    if(!emptyDrink())
    {
      myDrinkTop--;
    }
    else
    {
      cerr << "*** Order drink is empty -- can't remove drink ***" << endl;
    }
  }

  Food Order::topFood()
  {
    if(!emptyFood())
    {
      return (myFood[myFoodTop]);
    }
    else
    {
      cerr << "*** Order is empty -- returning random value ***" << endl;
      Food random;
      return random;
    }
  }

  Drink Order::topDrink()
  {
    if(!emptyDrink())
    {
      return (myDrink[myDrinkTop]);
    }
    else
    {
      cerr << "*** Order is empty -- returning random value ***" << endl;
      Drink random;
      return random;
    }
  }

  int Order::foodCount()
  {
    int foodCount = 0;
    for(int i = myFoodTop; i >= 0; i--)
    {
      if(myFood[i].getName() != "")
      {
        foodCount++;
      }
    }
    return foodCount;
  }

  int Order::drinkCount()
  {
    int drinkCount = 0;
    for(int i = myDrinkTop; i >= 0; i--)
    {
      if(myDrink[i].getName() != "")
      {
        drinkCount++;
      }
    }
    return drinkCount;
  }

  double Order::getTotalPrice()
  {
    double totalPrice = 0;
    for(int i = myFoodTop; i >= 0; i--)
    {
      totalPrice += myFood[i].getPrice();
    }
    for(int i = myDrinkTop; i >= 0; i--)
    {
      totalPrice += myDrink[i].getPrice();
    }
    return totalPrice;
  }

  void Order::display()
  {
    cout << "Order: " << endl << "\tFood (" << foodCount() << " items): " << endl;
    for(int i = myFoodTop; i >= 0; i--)
    {
      cout <<"\t\t";  
      myFood[i].display();
      cout << endl;
    }
    cout << "\tDrink (" << drinkCount() << " items): " << endl;
    for(int i = myDrinkTop; i >= 0; i--)
    {
      cout <<"\t\t";  
      myDrink[i].display();
      cout << endl;
    }
    cout << "\tOrder Total: $" << getTotalPrice() << endl << endl;
  }

  void Order::cancel(Automat & a)
  {
    while(!emptyFood())
    {
      a.enqueue(topFood());
      popFood();
    }

    while(!emptyDrink())
    {
      a.enqueue(topDrink());
      popDrink();
    }
  }

  void Order::purchase()
  {
    myFoodTop = -1;
    myDrinkTop = -1;
  }

  int Order::getTotalOrders()
  {
    return myTotalOrders;
  }

int main() 
{
    Automat a;
    a.enqueue(Food("Let's Potato Chips", 300, 1.50));
    a.enqueue(Food("Mini Donuts", 500, 1));
    a.enqueue(Drink("Coffee", 6, 5.50));
    a.enqueue(Drink("Nacho Drink", 22, 2.50));
    cout << "Starting Automat\n";
    a.display();

    Order o;
    o.push(a.frontFood());
    a.dequeueFood();
    o.push(a.frontDrink());
    a.dequeueDrink();
    cout << "Ordered one food, one drink\n";
    o.display();
    a.display();

    cout << "Canceled order\n";
    o.cancel(a);
    o.display();
    a.display();

    cout << "Ordered one food, one drink, purchased\n";
    o.push(a.frontFood());
    a.dequeueFood();
    o.push(a.frontDrink());
    a.dequeueDrink();
    o.purchase();
    o.display();
    a.display();
    return 0;
}