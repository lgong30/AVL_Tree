#include <iostream>
#include <random>
#include <cmath>
#include "avlTree.hpp"


int main()
{
	std::vector<int> myVec = {1,2,3,4,5,6,7,8,9,10,11,12};
	std::vector<int> myVecCopy = {1,2,3,4,5,6,7,8,9,10,11,12};

	//! basic check

	std::cout << "=============================================================================================\n";
	std::cout << "							          do basic check ...	     							   \n";
	std::cout << "=============================================================================================\n";
	AVL_Tree<int> aTree(myVec);

	std::vector<int> bfsData, parents,leftOrRight;
	aTree.bfs(bfsData,parents,leftOrRight);
	std::cout<< "data in bfs order:\n";
	for (auto d: bfsData)
		std::cout << d << " ";
	std::cout << std::endl;
	std::cout << "tree structure (parents):\n";
	for (auto p: parents)
		std::cout << p << " ";
	std::cout << std::endl;
	for (auto lr : leftOrRight)
		std::cout << lr << " ";
	std::cout << std::endl;

	std::cout << "do balance check:\n";
	std::cout << "  is it balanced: " << aTree.IsAVLTree() << std::endl;
	std::cout << "=============================================================================================\n";
	std::cout << "							       basic check passed ...   								   \n";
	std::cout << "=============================================================================================\n";

	//!
	const int MAX_NUMBER = 1e9;
	const int TEST_INSERTION = 1e4;
	const int TEST_DELETION = 1e3;
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution(0,MAX_NUMBER);
	std::uniform_int_distribution<int> index(0, TEST_INSERTION - 1);
	std::vector<double> data_copy;

	AVL_Tree<double> ATree2;
	double maximumHeight;
	std::cout << "\n\n";
	std::cout << "=============================================================================================\n";
	std::cout << "							do large-scale insertion check ...								   \n";
	std::cout << "=============================================================================================\n";
	for (int i = 0; i < TEST_INSERTION; ++i)
	{
		data_copy.push_back(distribution(generator));
		ATree2.insert(data_copy.back());
		if (i % 1000 == 0)
		{
			std::cout << "do balanced check (after inserting " << i + 1 << " elements):\n";
			std::cout << "  is it balanced: " << ATree2.IsAVLTree() << std::endl;
			
			maximumHeight = 1.44 * log2(ATree2.size() + 2) - 1;
			assert(maximumHeight > ATree2.height());
		}
	}
	std::cout << "=============================================================================================\n";
	std::cout << "                               insertion check passed                                        \n";
	std::cout << "=============================================================================================\n";
	std::cout << "\n\n";

	std::cout << "=============================================================================================\n";
	std::cout << "                             do large-scale deletion check ...                               \n";
	std::cout << "=============================================================================================\n";
	int elemNumBefore = ATree2.size();
	std::cout << "# of elements: " << elemNumBefore << std::endl;
	double deleteElem;
	for (int i = 0; i < TEST_DELETION; ++i)
	{
		deleteElem = data_copy[index(generator)];
		try
		{
			ATree2.remove(deleteElem);
		}
		catch (std::runtime_error &e)
		{
			std::cerr << "error occurs while deleting:\n" << "  " << e.what() << std::endl;
		}
		if (i % 100 == 0)
		{
			std::cout << "do balanced check (after deleting " << i + 1 << " elements):\n";
			std::cout << "  is it balanced: " << ATree2.IsAVLTree() << std::endl;

			maximumHeight = 1.44 * log2(ATree2.size() + 2) - 1;
			assert(maximumHeight > ATree2.height());
			std::cout << "# of elements: " << ATree2.size() << std::endl;
		}
	}

	std::cout << "=============================================================================================\n";
	std::cout << "                               deletion check passed                                        \n";
	std::cout << "=============================================================================================\n";
	std::cout << "\n\n";

	return 0;


}