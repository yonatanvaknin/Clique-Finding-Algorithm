#include <cstddef>
using namespace std;

struct split
{
	enum empties_t { empties_ok, no_empties };
};

template <typename Container> Container& splitString(Container& result,
													 const typename Container::value_type& s,
													 const typename Container::value_type& delimiters,
													 split::empties_t empties = split::empties_ok)
{
	result.clear();
	size_t current;
	size_t next = -1;
	do
	{
		if (empties == split::no_empties)
		{
			next = s.find_first_not_of(delimiters, next + 1);
			if (next == Container::value_type::npos) break;
			next -= 1;
		}
		current = next + 1;
		next = s.find_first_of(delimiters, current);
		result.push_back(s.substr( current, next - current));
	}
	while (next != Container::value_type::npos);
	return result;
}