//***************************************************************
// HEADER FILE USED IN PROJECT
//****************************************************************

#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>

	//***************************************************************
	// CLASS USED IN PROJECT
	//****************************************************************

	class product
	{
		int prono;
		char name[50];
		float cost, qty, disc;
		public:
			void create_product()
			{
				cout << "\nenter name of product: ";
				gets(name);
				cout << "\n\nenter unique product number: ";
				cin>>prono;
				cout << "\n enter the cost of product: ";
				cin >> cost;
				cout << "\nenter the discount available on product: ";
				cin >> disc;
			}

		void show_product()
		{
			cout << "\nThe Product No. of The Product : " << prono;
			cout << "\nThe Name of The Product : ";
			puts(name);
			cout << "\nThe Price of The Product : " << cost;
			cout << "\nDiscount : " << disc;
		}

		int getprono()
		{
			return prono;
		}

		float getcost()
		{
			return cost;
		}

		char * retname()
		{
			return name;
		}

		int getdisc()
		{
			return disc;
		}

	}; //class ends here

//***************************************************************
// global declaration for stream object, object
//****************************************************************

fstream fp;
product prod;
//***************************************************************
// function to write in file
//****************************************************************

void write_product()
{
	fp.open("Shop.txt", ios::out | ios::app);
	prod.create_product();
	fp.write((char * ) & prod, sizeof(product));
	fp.close();
	cout << "\n\nThe Product Has Been Created ";
	getch();
}
//***************************************************************
// function to read all records from file
//****************************************************************
void display_all()
{
	clrscr();
	cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	fp.open("Shop.txt", ios:: in );
	while (fp.read((char * ) & prod, sizeof(product)))
	{
		prod.show_product();
		cout << "\n\n====================================\n";
		getch();
	}
	fp.close();
	getch();
}
//***************************************************************
// function to read specific record from file
//****************************************************************
void display_sp(int n)
{
	int flag = 0;
	fp.open("Shop.txt", ios:: in );
	while (fp.read((char * ) & prod, sizeof(product)))
	{
		if (prod.getprono() == n)
		{
			clrscr();
			prod.show_product();
			flag = 1;
		}
	}
	fp.close();
	if (flag == 0)
		cout << "\n\nno such record entered exists in inventory.";
	getch();
}
//***************************************************************
// function to modify record of file
//****************************************************************
void modify_product()
{
	int no, found = 0;
	clrscr();
	cout << "\n\n For modification enter product no of record to be updated";
	cin >> no;
	fp.open("Shop.txt", ios:: in | ios::out);
	while (fp.read((char * ) & prod, sizeof(product)) && found == 0)
	{
		if (prod.getprono() == no)
		{
			prod.show_product();
			cout << "\nenter new details of the product" << endl;
			prod.create_product();
			int pos = -1 * sizeof(prod);
			fp.seekp(pos, ios::cur);
			fp.write((char * ) & prod, sizeof(product));
			cout << "\n\n\record has been updated in the system";
			found = 1;
		}
	}
	fp.close();
	if (found == 0)
		cout << "\n\n Record Not Found ";
	getch();
}
//***************************************************************
// function to delete record of file
//****************************************************************
void delete_product()
{
	int no;
	clrscr();
	cout << "\n\n\n\tDelete Record";
	cout << "\n\nPlease Enter The product no. of The Product You Want To Delete";
	cin >> no;
	fp.open("Shop.txt", ios:: in | ios::out);
	fstream fp2;
	fp2.open("Temp.txt", ios::out);
	fp.seekg(0, ios::beg);
	while (fp.read((char * ) & prod, sizeof(product)))
	{
		if (prod.getprono() != no)
		{
			fp2.write((char * ) & prod, sizeof(product));
		}
	}
	fp2.close();
	fp.close();
	remove("Shop.txt");
	rename("Temp.txt", "Shop.dat");
	cout << "\n\n\tRecord Deleted ..";
	getch();
}
//***************************************************************
// function to display all products price list
//****************************************************************

void menu()
{
	clrscr();
	int eof;
	fp.open("Shop.txt", ios:: in );
	if (!fp)
	{
		cout << "ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create file";

		cout << "\n\n\n Program is closing ....";
		getch();
		exit(0);
	}

	cout << "\n\n\t\tProduct MENU\n\n";
	cout << "\n";
	cout << "P.NO.\t\tNAME\t\tPRICE\n";
	cout << "\n";

	while (fp.read((char * ) & prod, sizeof(product)))
	{
		cout << prod.getprono() << "\t\t" << prod.retname() << "\t\t" << prod.getcost() << endl;
	}
	fp.close();
}

//***************************************************************
// function to place order and generating bill for Products
//****************************************************************

void place_order()
{
	int order_arr[50], quan[50], c = 0;
	float amt, damt, total = 0;
	char ch = 'Y';
	menu();
	cout << "\n PLACE YOUR ORDER";
	cout<<endl<<endl;
	do
	{
		cout << "\n\nEnter The Product No. Of The Product : ";
		cin >> order_arr[c];
		cout << "\nQuantity in number : ";
		cin >> quan[c];
		c++;
		cout << "\nwant to add another product ? (y/n)";
		cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	cout << "\n\nThanks for placing order";
	getch();
	clrscr();
	cout << "\n\n---- BILL----\n";
	cout << "\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount";

	for (int x = 0; x <= c; x++)
	{
		fp.open("Shop.txt", ios:: in );
		fp.read((char * ) & prod, sizeof(product));
		while (!fp.eof())
		{
			if (prod.getprono() == order_arr[x])
			{
				amt = prod.getcost() * quan[x];
				damt = amt - (amt * prod.getdisc() / 100);
				cout << "\n" << order_arr[x] << "\t" << prod.retname() <<
					"\t" << quan[x] << "\t\t" << prod.getcost() << "\t" << amt << "\t\t" << damt;
				total += damt;
			}
			fp.read((char * ) & prod, sizeof(product));
		}

		fp.close();
	}
	cout << "\n\n\t\t\t\t\tTOTAL = " << total;
	getch();
}
//ADDMINSTRATOR MENU FUNCTION
//
void admin_menu()
{
	clrscr();
	char ch2;
	cout << "\n\n\n\tadministrator menu";
	cout << "\n\n\t1.create a produce";
	cout << "\n\n\t2.show all exixting products";
	cout << "\n\n\t3.enter product no to get its data displayed as a query ";
	cout << "\n\n\t4.modify product details";
	cout << "\n\n\t5.delete product";
	cout << "\n\n\t6.view all products info";
	cout << "\n\n\t7.back to main menu";
	cout << "\n\n\tselect your task from above options and enter the task no (1-7) ";
	ch2 = getche();
	switch (ch2)
	{
	case '1':
		clrscr();
		write_product();
		break;
	case '2':
		display_all();
		break;
	case '3':
		int num;
		clrscr();
		cout << "\n\n\tPlease Enter The Product No. ";
		cin >> num;
		display_sp(num);
		break;
	case '4':
		modify_product();
		break;
	case '5':
		delete_product();
		break;
	case '6':
		menu();
		getch();
	case '7':
		break;
	default:
		cout << "\a";
		admin_menu();
   }
}
//***************************************************************
// THE MAIN FUNCTION OF PROGRAM
//****************************************************************
void main()
{

   clrscr();
	char ch;
	do
	{
		clrscr();
		cout << "\n\n\n\tWelcome to MAIN MENU of supermarket billing system.";
		cout << "\n\n\t01.select 1 if you are CUSTOMER";
		cout << "\n\n\t02.select 2 if you are ADMINISTRATOR";
		cout << "\n\n\t03.select 3 if you want to EXIT";
		cout << "\n\n\tPlease Select Your Option (1-3) ";
		ch = getche();
		switch (ch)
		{
		case '1':
			clrscr();
			place_order();
			getch();
			break;
		case '2':
			admin_menu();
			break;
		case '3':
			exit(0);
		default:
			cout << "\a";
		}
	} while (ch != '3');
	getch();
}

//***************************************************************
// END OF PROJECT

//***************************************************************