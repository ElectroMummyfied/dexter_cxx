#include "dexter.hxx"


int main (
	int argc,
	char *argv[]
)
{
	try {
		dxt::tensorf A;
		dxt::vec<dxt::ull> _addr;

		A.rank({{3, 3, 3}});
		for(dxt::ull it = 0; it < A.n_elem(); it++)
		{
			A.addr(it, _addr);
			// dxt::print(_addr);
			A.at(_addr) = it;
		}

		dxt::print(A);
	} catch(std::exception &ex) {
		std::cout << ex.what() << std::endl;
	}

	std::cout << "End of program. (press any key to continue... )\n";
	std::cin.get();
	return 0;
}
