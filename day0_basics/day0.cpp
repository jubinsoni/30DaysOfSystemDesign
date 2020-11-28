# include <iostream>

using namespace std;

class Book{
public:
	
	// properties
	string title;
	string author;
	int pages;

	// constructor
	Book(string,string,int);

	//functionality
	bool isThinBook();
};

Book::Book(string aTitle,string aAuthor,int aPages)
{
	this->title = aTitle;
	this->author = aAuthor;
	this->pages = aPages;
}

bool Book::isThinBook()
{
	if(this->pages < 300)
	{
		return true;
	}

	return false;
}

int main()
{
	Book book1("The Mamba Mentality: How I Play","Kobe Bryant",208);

	Book book2("Aircraft Encyclopedia","Orville & Wilbur Wright",4000);

	cout << "pages in book1 => " << book1.pages << endl;
	cout << "pages in book2 => " << book2.pages << endl;

	cout << "book1 thin? => " << book1.isThinBook() << endl;
	cout << "book2 thin? => " << book2.isThinBook() << endl;


	return 0;
}