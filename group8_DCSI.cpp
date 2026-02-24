#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

int main(void)
{
	
	/*	CUSTOMER INFORMATION */
	string name, ic_passport;
	int age;
	char member, student;
	
	/*	ORDER STORAGE */
	string orderName[20], orderDiscount[20];
	int orderQty[20], orderCount = 0;
	double orderFinal[20], grandTotal = 0;
	char more = 'Y';

	/*	Input: Customer Name
		- Uses getline so the user can enter spaces (ex : "Pey May Yan").
		- Loop prevents empty name input. */ 
	cout << "Enter Customer Name: ";
	getline(cin, name);
	while (name.empty())
	{
		cout << "Name cannot be empty. Enter again: ";
		getline(cin, name);
	}

	/*	Input: IC or Passport (user chooses)
		- Ask which one they want to enter
		- If IC: must be exactly 12 characters
		- If Passport: no specific requirement (just not empty) */
	string idType;

	cout << "Enter IC or Passport? (IC/Passport): ";
	cin >> idType;
	while (idType != "IC" && idType != "ic" && idType != "Passport" && idType != "passport")
	{
		cout << "Invalid. Type IC or Passport: ";
		cin >> idType;
	}

	cout << "Enter " << ((idType == "IC" || idType == "ic") ? "IC (12 digits)" : "Passport") << ": ";
	cin >> ic_passport;

	if (idType == "IC" || idType == "ic")
	{
		while (ic_passport.length() != 12)
		{
			cout << "Invalid IC. Must be exactly 12 characters. Enter again: ";
			cin >> ic_passport;
		}
	}
	else
	{
		while (ic_passport.empty())
		{
			cout << "Passport cannot be empty. Enter again: ";
			cin >> ic_passport;
		}
	}
	
	/*	Input: Age (1 - 150)
		Requirements:
		- Must be an integer
		- Must be within range
		If user types letters, cin fails:
		- clear() resets error flags
		- ignore() removes invalid input from buffer */
	cout << "Enter Age (1-150): ";
	while (!(cin >> age) || age < 1 || age > 150)
	{
		cout << "Invalid age. Enter 1-150: ";
		cin.clear(); // Clears error flags on the cin stream
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clears input buffer
	}

	/*	Input: Member status (Y/N)
		- Loop ensures only 'Y', 'y', 'N' or 'n' are accepted. */
	cout << "Member? (Y/N): ";
	cin >> member;
	while (member!='Y' && member!='y' && member!='N' && member!='n')
	{
		cout << "Invalid. Enter Y or N: ";
		cin >> member;
	}

	/*	Input: Student status (Y/N)
		- Loop ensures only 'Y', 'y', 'N' or 'n' are accepted. */
	cout << "Student? (Y/N): ";
	cin >> student;
	while (student!='Y' && student!='y' && student!='N' && student!='n')
	{
		cout << "Invalid. Enter Y or N: ";
		cin >> student;
	}

	/*	DISPLAY MENU
		Each item has:
		- base price
		- possible discounts (Member | Student | Senior) */
	cout << "\nMENU                     (Discounts: Member | Student | Senior (60+))\n";
	cout << "1. Grilled Chicken Set (RM18)           [ 10% | 15% | 5% ]\n";
	cout << "2. Beef Burger Combo (RM22)             [ 12% | 10% | 5% ]\n";
	cout << "3. Seafood Pasta (RM28)                 [ 15% | 12% | 8% ]\n";
	cout << "4. Vegetarian Rice Bowl (RM16)          [  8% | 10% | 5% ]\n";
	cout << "5. Family Pizza Set (RM45)              [ 10% |  8% | 6% ]\n";
	cout << "6. Dessert & Beverage Combo (RM14)      [ 12% | 10% | 7% ]\n";

	/*	ORDERING LOOP
		Keeps asking for items while user answers Y/y.
		Stops when:
		- user says 'N' or 'n'
		- array limit (20 orders) is reached */
	while (more == 'Y' || more == 'y')
	{
		if (orderCount >= 20) // Prevents writing past the array size (0-19).
			break;

		int code, qty;
		string itemName;
		double price = 0, memberDisc = 0, studentDisc = 0, seniorDisc = 0;

		/*	Input: Item Code (1-6)
			- Validates numeric input and range.
			- If invalid (letters/out of range), clear & ignore buffer, then ask again. */
		cout << "\nEnter Item Code (1-6): ";
		while (!(cin >> code) || code < 1 || code > 6)
		{
			cout << "Invalid code. Enter 1-6: ";
			cin.clear(); // Clears error flags on the cin stream
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clears input buffer
		}

		/*	Set item details based on code:
			- itemName
			- base price
			- discount percentages for member/student/senior */
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

		/*	Input: Quantity (> 0)
			- Ensures quantity is a positive integer and not zero. */
		cout << "Quantity: ";
		while (!(cin >> qty) || qty <= 0)
		{
			cout << "Invalid quantity. Enter again: ";
			cin.clear(); // Clears error flags on the cin stream
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clears input buffer
		}

		/*	Convert customer details into boolean flags.
			These flags will be used to pick the best discount. */
		bool isMember	= (member=='Y'||member=='y');
		bool isStudent	= (student=='Y'||student=='y');
		bool isSenior	= (age>=60);

		/*	Choose the best discount available (highest percentage).
			Start with 0% (None), then compare member/student/senior. */
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

		/*	Calculate final price:
			final = (base price * quantity) after applying bestDiscount */
		double finalPrice = price * qty * (1 - bestDiscount/100.0);

		/*	Save order into arrays at index = orderCount,
			then increase orderCount for the next order. */
		orderName[orderCount]=itemName;
		orderQty[orderCount]=qty;
		orderFinal[orderCount]=finalPrice;

		/*	Store discount label for receipt display. */
		if (bestDiscount>0)
			orderDiscount[orderCount]=bestType+"("+to_string((int)bestDiscount)+"%)";
		else
			orderDiscount[orderCount]="None(0%)";

		/*	Update grand total and move to next slot in the array. */
		grandTotal+=finalPrice;
		orderCount++;

		/*	Ask if user wants to add another item.
			Validate Y/y/N/n. */
		cout	<<	"Add another item? (Y/N): ";
		cin		>>	more;
		while (more != 'Y' && more != 'y' && more != 'N' && more != 'n' )
		{
			cout	<<	"Invalid. Enter Y or N: ";
			cin		>>	more;
		}
	}

	/*	RECEIPT OUTPUT
		- Prints all saved orders (0 to orderCount-1) and the grand total. */
	cout << "\n=========== RECEIPT ===========\n";
	cout << "Name: " << name << endl;
	cout << ((idType == "IC" || idType == "ic") ? "IC: " : "Passport: ") << ic_passport << endl;

	/*	Receipt table header */
	cout << left << setw(28) << "\nItem"
		 << setw(6) << "Qty"
		 << setw(18) << "Discount"
		 << "Price (RM)\n";

	/*	Print each ordered item */
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
