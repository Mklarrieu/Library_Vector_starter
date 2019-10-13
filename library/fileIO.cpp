#include "../includes_usr/fileIO.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
int loadBooks(std::vector<book> &books, const char* filename)
{
	ifstream bookFile;
	bookFile.open(filename);
	books.clear();
	if(!bookFile.is_open()){
		return COULD_NOT_OPEN_FILE;
	}

	book myBook;
	std::string line;
	std::string token;
	std::stringstream ss;
	const char CHAR_TO_SEARCH_FOR = ',';
	//int idNum = 0;

	if(bookFile.eof()){
		return NO_BOOKS_IN_LIBRARY;
	}

	while(!bookFile.eof()){
		getline(bookFile, line);
		ss<<line;
		if(line.empty()){
			break;
		}
		//myBook.book();
		//get book id
		getline(ss, token, CHAR_TO_SEARCH_FOR);
		myBook.book_id = atoi(token.c_str());

		//get title
		getline(ss, myBook.title, CHAR_TO_SEARCH_FOR);

		//get author
		getline(ss, myBook.author, CHAR_TO_SEARCH_FOR);

		//get checkout state
		getline(ss, token, CHAR_TO_SEARCH_FOR);
		int bookState = atoi(token.c_str());
		book_checkout_state cast = static_cast<book_checkout_state>(bookState);
		myBook.state = cast;
		//get patron id
		getline(ss, token, CHAR_TO_SEARCH_FOR);
		myBook.loaned_to_patron_id = atoi(token.c_str());

		books.push_back(myBook);
		ss.clear();

	}

	if(books.empty()){
		return NO_BOOKS_IN_LIBRARY;
	}

	bookFile.close();
	cout<<books.size()<<std::endl;

	return SUCCESS;
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char* filename)
{
	ofstream bookFile;
	bookFile.open(filename);
	if(!bookFile.is_open()){
		return COULD_NOT_OPEN_FILE;
	}
	if(books.empty()){
		return NO_BOOKS_IN_LIBRARY;
	}
	string bookData;
	for(int i = 0; i < books.size(); i++){
		bookData = std::to_string(books[i].book_id) + "," + books[i].title + "," + books[i].author +
				"," + std::to_string(books[i].state) + "," +
				std::to_string(books[i].loaned_to_patron_id);
		bookFile << bookData << std::endl;
	}

	if(bookFile.is_open()){
		bookFile.close();
	}
	return SUCCESS;
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char* filename)
{
	ifstream patronFile;
		patronFile.open(filename);
		patrons.clear();
		if(!patronFile.is_open()){
			return COULD_NOT_OPEN_FILE;
		}

		patron myPatron;
		std::string line;
		std::string token;
		std::stringstream ss;
		const char CHAR_TO_SEARCH_FOR = ',';
		//int idNum = 0;

		while(!patronFile.eof()){
			getline(patronFile, line);
			ss<<line;
			if(line.empty()){
				break;
			}
			//myBook.book();
			//get patron id
			getline(ss, token, CHAR_TO_SEARCH_FOR);
			myPatron.patron_id = atoi(token.c_str());

			//get name
			getline(ss, myPatron.name, CHAR_TO_SEARCH_FOR);

			//get number of books checkedout
			getline(ss, token, CHAR_TO_SEARCH_FOR);
			myPatron.number_books_checked_out = atoi(token.c_str());

			patrons.push_back(myPatron);
			ss.clear();


		}

		if(patrons.empty()){
			return NO_PATRONS_IN_LIBRARY;
		}


		return SUCCESS;
}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char* filename)
{
	ofstream patronFile;
		patronFile.open(filename);
		if(!patronFile.is_open()){
			return COULD_NOT_OPEN_FILE;
		}
		if(patrons.empty()){
			return NO_PATRONS_IN_LIBRARY;
		}
		string patronData;
		for(int i = 0; i < patrons.size(); i++){
			patronData = std::to_string(patrons[i].patron_id) + "," + patrons[i].name +
					"," + std::to_string(patrons[i].number_books_checked_out);
			patronFile << patronData << std::endl;
		}

		if(patronFile.is_open()){
			patronFile.close();
		}
		return SUCCESS;
}
