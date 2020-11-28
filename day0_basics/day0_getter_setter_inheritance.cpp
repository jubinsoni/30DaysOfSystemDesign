# include <iostream>

using namespace std;

class Book{

private:
	// properties
	string title;
	string author;
	int pages;

public:
	// constructor
	Book();

	// getters and setters
	string getTitle();
	void setTitle(string title);

	string getAuthor();
	void setAuthor(string author);

	int getPages();
	void setPages(int author);

	//functionality
	bool isThinBook();
};

Book::Book()
{
	title = "";
	author = "";
	pages = 0;
}

string Book::getTitle()
{
	return title;
}

void Book::setTitle(string title)
{
	this->title = title;
}

string Book::getAuthor()
{
	return author;
}

void Book::setAuthor(string author)
{
	this->author = author;
}

int Book::getPages()
{
	return pages;
}

void Book::setPages(int pages)
{
	this->pages = pages;
}

bool Book::isThinBook()
{
	if(this->pages < 300)
	{
		return true;
	}

	return false;
}

class SchoolBag : public Book
{
private:
	int size;
public:
	int getSize();
	void setSize(int size);

	string bagTitle();

	string bagOwner();
};

int SchoolBag::getSize()
{
	return size;
}

void SchoolBag::setSize(int size)
{
	this->size = size;
}

int main()
{
	Book book1;
	book1.setTitle("The Mamba Mentality: How I Play");
	book1.setAuthor("Kobe Bryant");
	book1.setPages(208);

	Book book2;
	book2.setTitle("Aircraft Encyclopedia");
	book2.setAuthor("Orville & Wilbur Wright");
	book2.setPages(4000);

	cout << "pages in book1 => " << book1.getPages() << endl;
	cout << "pages in book2 => " << book2.getPages() << endl;

	cout << "book1 thin? => " << book1.isThinBook() << endl;
	cout << "book2 thin? => " << book2.isThinBook() << endl;

	cout << "-----------------" << endl;

	SchoolBag sbag;
	sbag.setSize(2);
	sbag.setTitle("green bag");
	sbag.setAuthor("jubin");

	cout << "No of books in bag => " << sbag.getSize() << endl;
	cout << "bag title => " << sbag.getTitle() << endl;
	cout << "bag author => " << sbag.getAuthor() << endl;


	return 0;
}