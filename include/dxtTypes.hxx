#include "dxtHeaders.hxx"

namespace dxt
{
    typedef unsigned long long ull;

    template <class T>
    using vec = std::vector<T>;

	template <class T>
	class tensor;

	typedef tensor<float> tensorf;
}