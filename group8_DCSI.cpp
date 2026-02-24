#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

int main(void)
{
	string name, ic_passport;
	int age;
	char member, student;

	string orderName[20], orderDiscount[20];
	int orderQty[20], orderCount = 0;
	double orderFinal[20], grandTotal = 0;
	char more = 'Y';

	cout << "Enter Customer Name: ";
	getline(cin, name);
	while (name.empty())
	{
		cout << "Name cannot be empty. Enter again: ";
		getline(cin, name);
	}

	cout	<< "Enter IC/Passport (12 digits): ";
	cin		>> ic_passport;
	while (ic_passport.length() != 12)
	{
		cout	<< "Invalid IC/Passport. Must be exactly 12 digits: ";
		cin		>> ic_passport;
	}

	cout << "Enter Age (1-150): ";
	while (!(cin >> age) || age < 1 || age > 150)
	{
		cout << "Invalid age. Enter 1-150: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	cout << "Member? (Y/N): ";
	cin >> member;
	while (member!='Y' && member!='y' && member!='N' && member!='n')
	{
		cout << "Invalid. Enter Y or N: ";
		cin >> member;
	}

	cout << "Student? (Y/N): ";
	cin >> student;
	while (student!='Y' && student!='y' && student!='N' && student!='n')
	{
		cout << "Invalid. Enter Y or N: ";
		cin >> student;
	}

	cout << "\nMENU                     (Discounts: Member | Student | Senior (60+))\n";
	cout << "1. Grilled Chicken Set (RM18)           [ 10% | 15% | 5% ]\n";
	cout << "2. Beef Burger Combo (RM22)             [ 12% | 10% | 5% ]\n";
	cout << "3. Seafood Pasta (RM28)                 [ 15% | 12% | 8% ]\n";
	cout << "4. Vegetarian Rice Bowl (RM16)          [  8% | 10% | 5% ]\n";
	cout << "5. Family Pizza Set (RM45)              [ 10% |  8% | 6% ]\n";
	cout << "6. Dessert & Beverage Combo (RM14)      [ 12% | 10% | 7% ]\n";

	while (more == 'Y' || more == 'y')
	{
		if (orderCount >= 20)
			break;

		int code, qty;
		string itemName;
		double price = 0, memberDisc = 0, studentDisc = 0, seniorDisc = 0;

		cout << "\nEnter Item Code (1-6): ";
		while (!(cin >> code) || code < 1 || code > 6)
		{
			cout << "Invalid code. Enter 1-6: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		switch(code)
		{
			case 1: itemName="Grilled Chicken Set"; price=18;
					memberDisc=10; studentDisc=15; seniorDisc=5; break;
			case 2: itemName="Beef Burger Combo"; price=22;
					memberDisc=12; studentDisc=10; seniorDisc=5; break;
			case 3: itemName="Seafood Pasta"; price=28;
					memberDisc=15; studentDisc=12; seniorDisc=8; break;
			case 4: itemName="Vegetarian Rice Bowl"; price=16;
					memberDisc=8; studentDisc=10; seniorDisc=5; break;
			case 5: itemName="Family Pizza Set"; price=45;
					memberDisc=10; studentDisc=8; seniorDisc=6; break;
			case 6: itemName="Dessert & Beverage Combo"; price=14;
					memberDisc=12; studentDisc=10; seniorDisc=7; break;
		}

		cout << "Quantity: ";
		while (!(cin >> qty) || qty <= 0)
		{
			cout << "Invalid quantity. Enter again: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		bool isMember	= (member=='Y'||member=='y');
		bool isStudent	= (student=='Y'||student=='y');
		bool isSenior	= (age>=60);

		double bestDiscount = 0;
		string bestType = "None";

		if (isMember && memberDisc > bestDiscount)
		{
			bestDiscount = memberDisc;
			bestType = "Member";
		}
		if (isStudent && studentDisc > bestDiscount)
		{
			bestDiscount = studentDisc;
			bestType = "Student";
		}
		if (isSenior && seniorDisc > bestDiscount)
		{
			bestDiscount = seniorDisc;
			bestType = "Senior";
		}

		double finalPrice = price * qty * (1 - bestDiscount/100.0);

		orderName[orderCount]=itemName;
		orderQty[orderCount]=qty;
		orderFinal[orderCount]=finalPrice;

		if (bestDiscount>0)
			orderDiscount[orderCount]=bestType+"("+to_string((int)bestDiscount)+"%)";
		else
			orderDiscount[orderCount]="None(0%)";

		grandTotal+=finalPrice;
		orderCount++;

		cout	<<	"Add another item? (Y/N): ";
		cin		>>	more;
		while (more != 'Y' && more != 'y' && more != 'N' && more != 'n' )
		{
			cout	<<	"Invalid. Enter Y or N: ";
			cin		>>	more;
		}
	}

	cout << "\n=========== RECEIPT ===========\n";
	cout << "Name: " << name << endl;
	cout << "IC/Passport: " << ic_passport << endl;

	cout << left << setw(28) << "\nItem"
		 << setw(6) << "Qty"
		 << setw(18) << "Discount"
		 << "Final (RM)\n";

	int i = 0;
	while (i < orderCount)
	{
		cout << setw(28) << orderName[i]
			 << setw(6) << orderQty[i]
			 << setw(18) << orderDiscount[i]
			 << fixed << setprecision(2) << orderFinal[i] << endl;
		i++;
	}

	cout << "\nGrand Total: RM " << fixed << setprecision(2) << grandTotal << endl;

	return (0);
}
