#include <iostream>
#include <vector>
#include <algorithm>  //std::rotate
#include <iterator>
#include <fstream>
#include <iomanip>



//using namespace std;

/****************************************
* Declarations                          *
*****************************************/

using Test = bool(*)(int);





//Generic class to write an item of type T to a stream
template<typename T>
class Formatter
{
public:

    Formatter(std::ostream& os, int width, int per_line)
        : os_(os), per_line_(per_line), width_(width)
    {}

    void operator()(const T& t)
    {
        os_ << std::setw(width_) << t;
        if (++outputted_ % per_line_ == 0)
            os_ << "\n";
    }

private:
    std::ostream&  os_;		//output stream
    const int per_line_;	//number of columns per line
    const int width_;		//column width
    int   outputted_{ 0 };	//counter of number of items written to os_
};


namespace TND004
{
    //Divide-and-conquer algorithm
    void stable_partition(std::vector<int>& V, Test p);

    //Iterative algorithm
    void stable_partition_iterative(std::vector<int>& V, Test p);
}

void execute(std::vector<int>& V);

bool even(int i);


/****************************************
* Main                                  *
*****************************************/

int main()
{
    /*****************************************************
    * TEST PHASE 1                                       *
    ******************************************************/
    std::cout << "TEST PHASE 1\n\n";

    std::vector<int> seq1{ 1, 2 };

    std::cout << "Sequence: ";
    std::copy(seq1.begin(), seq1.end(), std::ostream_iterator<int>(std::cout, " "));

    execute(seq1);

    /*****************************************************
    * TEST PHASE2                                        *
    ******************************************************/
    std::cout << "\n\nTEST PHASE 2\n\n";

    std::vector<int> seq2{ 2 };

    std::cout << "Sequence: ";
    std::copy(seq2.begin(), seq2.end(), std::ostream_iterator<int>(std::cout, " "));

    execute(seq2);

    /*****************************************************
    * TEST PHASE3                                        *
    ******************************************************/
    std::cout << "\n\nTEST PHASE 3\n\n";

    std::vector<int> seq3;

    std::cout << "Sequence: empty";

    execute(seq3);

    /*****************************************************
    * TEST PHASE 4                                       *
    ******************************************************/
    std::cout << "\n\nTEST PHASE 4\n\n";

    std::vector<int> seq4{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    std::cout << "Sequence: ";
    std::copy(seq4.begin(), seq4.end(), std::ostream_iterator<int>(std::cout, " "));

    execute(seq4);

    /*****************************************************
    * TEST PHASE4                                        *
    ******************************************************/
    std::cout << "\n\nTEST PHASE 4: test with long sequence loaded from a file\n\n";

    std::ifstream file("test_data.txt");

    if (!file)
    {
        std::cout << "Could not open test data file!!\n";
        return 0;
    }

    std::vector<int> seq5;

    std::istream_iterator<int> in_itr(file);
    std::istream_iterator<int> in_itr_end;

    //read the data in the file into seq5
    std::copy(in_itr, in_itr_end, back_inserter(seq5));

    std::cout << "Number of items in the sequence: " << seq5.size() << std::endl;

    std::vector<int> seq6(seq5);

    std::cout << "\n After stable partition ..." << std::endl;

    TND004::stable_partition_iterative(seq5, even);

    TND004::stable_partition(seq6, even); //recursive

    if ( std::equal(begin(seq5), end(seq5), begin(seq6)) )
    {
        //Display
        std::for_each(begin(seq6), end(seq6), Formatter<int>(std::cout, 8, 5));
    }
    else
    {
        std::cout << "Error: recursive and iterative algorithms give different results!!" << std::endl;
    }

    std::cout << std::endl;

	
    return 0;
}

/****************************************
* Functions definitions                 *
*****************************************/

bool even(int i)
{
    return i % 2 == 0;
}

namespace TND004
{
    //Divide-and-conquer algorithm
    std::vector<int>::iterator stable_partition(std::vector<int>& V, std::vector<int>::iterator first, std::vector<int>::iterator last, Test p)
    {
		if (V.size() == 0)
		{
			return first;
		}
		

		

		
	
		if (first == last-1) //base case
		{

			
			if (p(*first))
			{
				return first +1;
			}
			else
			{
				return first;
			}
			
			
		}

		std::vector<int>::iterator mid = first + (std::distance(first, last) / 2);
		std::vector<int>::iterator right = stable_partition(V, mid, last, p);  //right division
		std::vector<int>::iterator left = stable_partition(V, first, mid, p); //left devision



		return std::rotate(left, mid, right);

      
    }
}


void TND004::stable_partition(std::vector<int>& V, Test p)
{
    TND004::stable_partition(V, std::begin(V), std::end(V), p);
}


//Iterative algorithm
void TND004::stable_partition_iterative(std::vector<int>& V, Test p)
{
	int counter = 0;


	for (int i = V.size() -1; i > -1; i--)
	{
		if (p(V[i+ counter]))
		{
			V.insert(V.begin(), V[(i +counter)]);
			V.erase(V.begin()+i+counter+1);

			counter++;
		}

	}


}


void execute(std::vector<int>& V)
{
    std::vector<int> _copy(V);

    std::cout << "\nIterative stable partition: ";
    TND004::stable_partition_iterative(V, even);

    //Display
    std::copy(std::begin(V), std::end(V), std::ostream_iterator<int>(std::cout, " "));

    std::cout << "\nDivide-and-conquer stable partition: ";
    TND004::stable_partition(_copy, even);

    //Display
    std::copy(std::begin(_copy), std::end(_copy), std::ostream_iterator<int>(std::cout, " "));
}
