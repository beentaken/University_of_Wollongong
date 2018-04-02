#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

// helper or supporting functions should be placed here



bool same_elements(vector<int> a, vector<int> b)
{
	if (a.size() != b.size())
		return false;
	vector<int>::iterator ite_a;
	vector<int>::iterator ite_b;
	vector<int>::iterator ite_1;
	vector<int>::iterator ite_2;
	for (ite_a = a.begin(); ite_a != a.end(); ite_a++) {
		for (ite_b = b.begin(); ite_b != b.end(); ite_b++) {
			if (*ite_a == *ite_b) {
				ite_1 = ite_a;
				ite_2 = ite_b;
				while (*ite_1 == *ite_2) {
					if (ite_1 == a.end())
						ite_1 = a.begin();
					if (ite_2 == b.end())
						ite_2 = b.begin();
					if ((ite_1 == ite_a) && (ite_2 == ite_b))
						return true;
					ite_1++;
					ite_2++;
				}
			}
		}
	}
	return false;
}   

void remove_duplicates(vector<int>& a)
{

}

int main()
{
	int a[9] = {1,4,9,16,9,7,4,9,11};
	int b[9] = {11,1,4,9,16,9,7,4,9};

    vector<int>  va(a, a + sizeof(a) / sizeof(a[0]));	// create vector va from array a
	vector<int>  vb(b, b + sizeof(b) / sizeof(b[0]));	// create vector vb from array b

	// check whether va and vb have same elements
	cout << "The vectors va and vb have ";
	if (!same_elements(va, vb)) cout << "not ";
	cout << "the same elements.\n";

	// remove duplicate elements from va
	remove_duplicates(va);

	// output elements in va using copy function and stream iterator
	// using space as sepratator between elements
	copy(....);
	
	cout<<endl;
	
    return 0;
}
