
#include "BinarySearchTree.h"
//#include "BinaryTree.h"
#include "Card.h"
#include <cstdlib>
#include <ctime>

using namespace std;
typedef Card* PTR_CARD;

int comparePips(const PTR_CARD &left, const PTR_CARD &right)
{
    int diff = left->getPips() - right->getPips();
    if (diff < 0)
	   return -1;
    else if (diff > 0)
	   return 1;
    diff = left->getSuitNum() - right->getSuitNum();
    if (diff == 0)
	   return 0;
    else if (diff < 0)
	   return -1;
    else 
	   return 1;
}
int compareSuits(const PTR_CARD &left, const PTR_CARD &right)
{
    if (*left == *right)
	   return 0;
    int diff = left->getSuitNum() - right->getSuitNum();
    if (diff < 0)
	   return -1;
    else if (diff == 0 && left->getPips() < right->getPips())
	   return -1;
    else
	   return 1;

}
void displayPTR_CARD(PTR_CARD &ptrCard)
{
    cout << *ptrCard;
}
void displaySuitPTR_CARD(PTR_CARD &ptrCard)
{
    cout << *(ptrCard->getSuitName()) << ", " << *(ptrCard->getPipsName()) << endl;
}
void fillTree(BinarySearchTree<PTR_CARD>* firstTree, BinarySearchTree<PTR_CARD>* secondTree)
{
    PTR_CARD randomCard;
    srand(time(NULL));
    for (int i = 0; i < 25; i++)
    {
	   randomCard = new Card;
	   randomCard->setPips(rand() % 14 + 1);
	   randomCard->setSuit(rand() % 4);
	   firstTree->insert(randomCard);
	   secondTree->insert(randomCard);
    }
    
}


void testBST(BinarySearchTree<PTR_CARD> *ptree)
{
    int tempPips, tempSuitNum;
    PTR_CARD searchItem;
    PTR_CARD pfoundItem;
    string prompt("\n\nEnter a Card (1-13  0-4) that should be in the tree: ");

    for (int i = 0; i < 2; ++i)
    {
	   cout << prompt;
	   cin >> tempPips >> tempSuitNum;
	   searchItem = new Card(tempPips, tempSuitNum);
	   if (ptree->getEntry(searchItem, pfoundItem))
	   {
		  cout << "Found : " << *pfoundItem << endl;
	   }
	   else
		  cout << *searchItem << " not found\n";

	   delete searchItem;
	   prompt = "\nEnter a Card (1-13  0-4) that should NOT be in the tree: ";
    } // end for

} // end testBST

void testCopyAndAssign(BinarySearchTree<PTR_CARD> *ptree1,
    BinarySearchTree<PTR_CARD> *ptree2)
{
    BinarySearchTree<PTR_CARD> *localPtrTree;

    localPtrTree = new BinarySearchTree<PTR_CARD>(*ptree1);
    cout << "\n\nThe local tree from copy constructor copying Pips-ordered tree\n";
    localPtrTree->inOrder(displayPTR_CARD);
    delete localPtrTree;

    cout << "\nChecking if Original Pips-ordered Tree was not changed: \n";
    ptree1->inOrder(displayPTR_CARD);

    { // BRACKETS ARE HERE TO CHECK WHEN IT GOES OUT OF SCOPE
	   BinarySearchTree<PTR_CARD> localTree(compareSuits);
	   localTree = *ptree2; // tests operator=
	   cout << "\nThe local tree from operator= copying Suit-ordered tree\n";
	   localTree.inOrder(displayPTR_CARD);
    }
    cout << "\nChecking if Original Suit-ordered Tree was not changed: \n";
    ptree2->inOrder(displayPTR_CARD);
}

// YOU WRITE THIS ONE (DESCRIBED ON THE ASSIGNMENT):
void testDelete(BinarySearchTree <PTR_CARD> *ptree1,
    BinarySearchTree<PTR_CARD> *ptree2)
{
    // fill in here as described on Prog. HW#4 assignment
    PTR_CARD first = 0;
    PTR_CARD last = 0;
    ptree1->getFirst(first);
    ptree1->getLast(last);
    cout << "first card "<< *first << "last card "<< *last << endl;
    if (ptree1->remove(first))
	   cout << "first card successfully removed! " << endl;
    if(ptree1->remove(last))
	   cout << "last card successfully removed! " << endl;
    ptree2->getFirst(first);
    ptree2->getLast(last);
    cout << "first card " << *first << "last card " << *last << endl;
    if (ptree2->remove(first))
	   cout << "first card successfully removed! " << endl;
    if (ptree2->remove(last))
	   cout << "last card successfully removed! " << endl;
};

// call this function as specified near the end of HW#4 assignment:
void deletePTR_CARD(PTR_CARD &ptrCard)
{
    if (ptrCard != 0)
	   delete ptrCard;
    ptrCard = 0;
};


int main()
{
    BinarySearchTree<PTR_CARD>* firstTree;  
    BinarySearchTree<PTR_CARD>* secondTree;
    firstTree = new BinarySearchTree<PTR_CARD>(comparePips);
    secondTree = new BinarySearchTree<PTR_CARD>(compareSuits);
    fillTree(firstTree, secondTree);
    cout << endl <<"Pips Sorted Tree inOrder Traversal: " << endl;
    firstTree->inOrder(displayPTR_CARD);
    cout << endl <<"Suit Sorted Tree inOrder Traversal: " << endl;
    secondTree->inOrder(displaySuitPTR_CARD);
    testBST(firstTree);
    testBST(secondTree);
    testDelete(firstTree, secondTree);
    testCopyAndAssign(firstTree, secondTree);
    firstTree->postOrder(deletePTR_CARD);
    firstTree->clear();
    secondTree->clear();

    system("pause");
    return 0;
}

/*


Pips Sorted Tree inOrder Traversal:
Ace of Clubs
Ace of Diamonds
Ace of Hearts
Ace of Spades
Ace of Spades
2 of Hearts
2 of Spades
3 of Clubs
3 of Hearts
4 of Diamonds
5 of Clubs
5 of Spades
5 of Spades
6 of Diamonds
6 of Hearts
7 of Clubs
7 of Diamonds
7 of Diamonds
9 of Clubs
9 of Diamonds
10 of Clubs
10 of Hearts
Jack of Diamonds
Jack of Hearts
King of Hearts

Suit Sorted Tree inOrder Traversal:
Clubs, Ace
Clubs, 3
Clubs, 5
Clubs, 7
Clubs, 9
Clubs, 10
Diamonds, Ace
Diamonds, 4
Diamonds, 6
Diamonds, 7
Diamonds, 7
Diamonds, 9
Diamonds, Jack
Hearts, Ace
Hearts, 2
Hearts, 3
Hearts, 6
Hearts, 10
Hearts, Jack
Hearts, King
Spades, Ace
Spades, Ace
Spades, 2
Spades, 5
Spades, 5


Enter a Card (1-13  0-4) that should be in the tree: 2 2
Found : 2 of Hearts


Enter a Card (1-13  0-4) that should NOT be in the tree: 5 2
5 of Hearts
not found


Enter a Card (1-13  0-4) that should be in the tree: 2 3
Found : 2 of Spades


Enter a Card (1-13  0-4) that should NOT be in the tree: 9 2
9 of Hearts
not found
first card Ace of Clubs
last card King of Hearts

first card successfully removed!
last card successfully removed!
first card Ace of Clubs
last card 5 of Spades

first card successfully removed!
last card successfully removed!


The local tree from copy constructor copying Pips-ordered tree
Ace of Diamonds
Ace of Hearts
Ace of Spades
Ace of Spades
2 of Hearts
2 of Spades
3 of Clubs
3 of Hearts
4 of Diamonds
5 of Clubs
5 of Spades
5 of Spades
6 of Diamonds
6 of Hearts
7 of Clubs
7 of Diamonds
7 of Diamonds
9 of Clubs
9 of Diamonds
10 of Clubs
10 of Hearts
Jack of Diamonds
Jack of Hearts

Clearing old tree


Checking if Original Pips-ordered Tree was not changed:
Ace of Diamonds
Ace of Hearts
Ace of Spades
Ace of Spades
2 of Hearts
2 of Spades
3 of Clubs
3 of Hearts
4 of Diamonds
5 of Clubs
5 of Spades
5 of Spades
6 of Diamonds
6 of Hearts
7 of Clubs
7 of Diamonds
7 of Diamonds
9 of Clubs
9 of Diamonds
10 of Clubs
10 of Hearts
Jack of Diamonds
Jack of Hearts

The local tree from operator= copying Suit-ordered tree
3 of Clubs
5 of Clubs
7 of Clubs
9 of Clubs
10 of Clubs
Ace of Diamonds
4 of Diamonds
6 of Diamonds
7 of Diamonds
7 of Diamonds
9 of Diamonds
Jack of Diamonds
Ace of Hearts
2 of Hearts
3 of Hearts
6 of Hearts
10 of Hearts
Jack of Hearts
King of Hearts
Ace of Spades
Ace of Spades
2 of Spades
5 of Spades

Clearing old tree


Checking if Original Suit-ordered Tree was not changed:
3 of Clubs
5 of Clubs
7 of Clubs
9 of Clubs
10 of Clubs
Ace of Diamonds
4 of Diamonds
6 of Diamonds
7 of Diamonds
7 of Diamonds
9 of Diamonds
Jack of Diamonds
Ace of Hearts
2 of Hearts
3 of Hearts
6 of Hearts
10 of Hearts
Jack of Hearts
King of Hearts
Ace of Spades
Ace of Spades
2 of Spades
5 of Spades

Clearing old tree


Clearing old tree

Press any key to continue . . .

*/