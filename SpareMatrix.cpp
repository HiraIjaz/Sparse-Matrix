//Question#2
//Hira Ijaz
//19l-2377
//CS2-G1
#include<iostream>
using namespace std;

int mystrlen(char* str) {
	if (str != nullptr) {
		int size = 0;
		for (; str[size] != '\0'; size++);
		return size;
	}
	return 0;
}

bool mystrcmp(char* str, char* str1) {
	bool match = true;
	if (mystrlen(str) != mystrlen(str1)) {
		return false;
	}
	else {
		for (int i = 0; i < mystrlen(str1) && match == true; i++) {
			if (str[i] == str1[i]) {
				match = true;
			}
			else match = false;
		}
		if (match == true) {
			return true;
		}
		else
			return false;
	}
}

void mystrcpy(char* destination, char* source) {
	if (source != nullptr) {

		for (int i = 0; i < (int)strlen(source); i++) {
			destination[i] = source[i];
		}
		destination[strlen(source)] = '\0';
	}
}
//Dessert Class
class DessertItem{
	char* name;
public:
	DessertItem() {
		name = nullptr;
	}
	DessertItem(char* n) {
		name = new char[strlen(n) + 1];
		mystrcpy(this->name, n);
	}
	DessertItem(const DessertItem& obj) {
		this->name = new char[strlen(obj.name) + 1];
		mystrcpy(this->name, obj.name);
	}
	~DessertItem() {
		if (name != nullptr) delete[]name;
	}
	DessertItem& operator=(const DessertItem& obj) {
		this->name = new char[strlen(obj.name) + 1];
		mystrcpy(this->name, obj.name);
		return *this;
	}
	virtual int getCost() {
		return 0;
	}
	virtual int getTax() {
		return 0;
	}
	virtual void print() {
		cout << "Name" << name << endl;
	}


};
class Cookie :public DessertItem{
	int number;
	int price;
public:
	Cookie() {
		number = 0;
		price = 0;

	}
	Cookie(const Cookie&obj) {
		this->price = obj.price;
		this->number = obj.number;

	}
	Cookie(int x, int y, char* n):DessertItem(n) {
		this->price = x;
		this->number = y;

	}
	~Cookie() {

	}
	int getCost() {
		int cost;
		cost = (number / 12) * price;
		return cost;
	}
	int getTax() {
		
		int tax;
		tax =( getCost()/2)*100;
		return tax;

	}
	void print() {
	DessertItem::print();
		cout << "Quantity" << number<<endl;
		cout << "Price per dozen" << price << endl;
	}
};
class Icecream :public DessertItem {
	int cost;
	char* flavourName;
public:
	Icecream(){
		cost = 0;
		flavourName = nullptr;
	}
	Icecream(int x, char* f, char* n):DessertItem(n) {
		this->flavourName = new char[strlen(f) + 1];
		mystrcpy(this->flavourName, f);
		this->cost = x;
	}
	Icecream(const Icecream &obj) {
		this->flavourName = new char[strlen(obj.flavourName) + 1];
		mystrcpy(this->flavourName, obj.flavourName);
		this->cost = obj.cost;

	}
	Icecream operator=(const Icecream& obj) {
		this->flavourName = new char[strlen(obj.flavourName) + 1];
		mystrcpy(this->flavourName, obj.flavourName);
		this->cost = obj.cost;
	}
	~Icecream() {
		if (flavourName != nullptr) delete[]flavourName;
	}
	int getCost() {
		return cost;

	}
	int getTax() {
		int tax;
		tax = (getCost() / 2) * 100;
		return tax;

	}
	void print() {
	DessertItem::print();
		cout << "Flavour Name" << flavourName << endl;
		cout << "Cost" << cost << endl;
	}


};
class Sundae :public Icecream {
	int toppingCost;
public:
	Sundae(){
		toppingCost = 0;
	}
	Sundae(int x, int y, char* f,char*n):Icecream(y,f,n) {
		this->toppingCost = x;
	}
	int getCost() {
		int cost;
		cost = Icecream::getCost() + toppingCost;
		return cost;
	}
	int getTax() {
		int tax;
		tax = (getCost()/2)*100;
		return tax;
	}
	void print() {
	Icecream::print();
		cout << "Topping Price" << toppingCost;
	}
	~Sundae() {

	}

};
class Order {
	DessertItem** itemList;
	int noOfItems;
public:
	Order() {
		itemList=nullptr;
	    noOfItems=0;
	}
	Order(int x) {
		noOfItems = x;
		itemList = new DessertItem*[x];
	}
	~Order() {
		if (itemList != nullptr) {
			for (int i = 0; i < noOfItems; i++) {
				delete[] itemList[i];
			}
			delete[] itemList;
		}

	}
	void placeOrder() {
		int userChoice;
		int i = 0, itemCount = 0;
		while (i < this->noOfItems)
		{
			cout << "Choose Item you want to add\n";
			cin >> userChoice;
			if (userChoice == 1)
			{
				int no, price;
				//take parameters from user needed for a Cookie
				char name[20] = "Cookie";
				cout << "Enter Number Of Cookies"<<endl;
				cin >> no;
				cout << endl;
				cout << "Enter Price per dozen" << endl;
				cin >> price;
				itemList[itemCount++] = new Cookie(price, no, name);
					//making base class pointer //point cookie object
			}
			else if (userChoice == 2)
			{
				//take parameters from user needed for an IceCream
				char name[20] = "Icecream";
				int cost;
				char flavourName[30];
				cout << "Enter Cost: ";
				cin >> cost;
				cin.ignore();
				cout << "Enter Flavour Name: ";
				cin.getline(flavourName,30); cin.clear(); cin.sync(); cout << endl;
				itemList[itemCount++] = new Icecream(cost, flavourName, name);
					//making base class pointer //point IceCream object
			}
			else if (userChoice == 3)
			{
				//take parameters from user needed for a Sundae
				char name[20] = "Sundae";
				int toppingprice;
				int cost;
				
				char flavourName[30];
				cout << "Enter Cost: ";
				cin >> cost;
				cout << "Enter Flavour Name: ";
				cin.ignore();
				cin.getline(flavourName, 30); cin.clear(); cin.sync(); cout << endl;
				cout << "Enter Topping Price: ";
				cin >> toppingprice;
				itemList[itemCount++] = new Sundae(toppingprice, cost, flavourName, name);
					//making base class pointer //point Sundae object
			}
			i++;

		}
	}
	void PrintOrder() {
		for (int i = 0; i < noOfItems; i++) {
			itemList[i]->print();
		}
	}
	int TotalTax() {
		int totaltax=0;
		for (int i = 0; i < noOfItems; i++) {
			totaltax=totaltax+itemList[i]->getTax();
		}
		return totaltax;
	}
	int TotalCost() {
		int totalcost=0;
		for (int i = 0; i < noOfItems; i++) {
			totalcost = totalcost + itemList[i]->getCost();
		}
		return totalcost;
	}



};

int main() {
	int totalOrders;
	cout << "How many orders you want to place ?";
	cin >> totalOrders;
	Order** ordersList = new Order * [totalOrders];
	for (int i = 0; i < totalOrders; i++)
	{
		int itemsCount;
		cout << "How many items you want: ";
		cin >> itemsCount;
		ordersList[i] = new Order(itemsCount);
		ordersList[i]->placeOrder();
	}
	//diplay all the orders here
	for (int i = 0; i < totalOrders; i++) {
		ordersList[i]->PrintOrder();
	}
	int TotalCost;
	//Find totalCost (sum of costs of all items in list without tax) and print it.
	for (int i = 0; i < totalOrders; i++) {
		TotalCost = ordersList[i]->TotalCost();
		cout << "TotalCost of Order " << i + 1 << "is" << TotalCost;
	}
	int TotalTax;
	//Find totalCost (sum of taxes of all items in list) and print it.
	for (int i = 0; i < totalOrders; i++) {
		TotalTax = ordersList[i]->TotalTax();
		cout << "Total Tax of Order" << i + i << "is" << TotalTax;
	}
	//delete the dynamially allocated memory.
	if (ordersList != nullptr) {
		for (int i = 0; i < totalOrders; i++) {
			delete[] ordersList[i];
		}
		delete[]ordersList;
	}
}