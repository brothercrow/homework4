
#include "BinarySearchTree.h"
#include "BinaryTree.h"
#include "Card.h"


using namespace std;


/*

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
};

// call this function as specified near the end of HW#4 assignment:
void deletePTR_CARD(PTR_CARD &ptrCard)
{
    if (ptrCard != 0)
	   delete ptrCard;
    ptrCard = 0;
};

*/
int main()
{

    return 0;
}