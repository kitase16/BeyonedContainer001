#include <iostream>
#include <memory>
#include <cstdint>


struct B4ed {
	void* Memory = nullptr;
	std::intmax_t Size = -1;
	typedef std::shared_ptr<B4ed> Shared;

	virtual ~B4ed() {
		delete[] Memory;
		Size = 0;
	}
};

struct B4edr:B4ed{
	B4edr::Shared  S= std::make_shared<decltype(*this)>();
};
template<class T>
struct B4edv {
	T* Memory = nullptr;
	std::intmax_t Size = -1;
	//typedef std::shared_ptr<B4ed> Shared;
};
template<class T>
const B4ed& NEW(std::size_t S) {
	B4ed X;
	X.Memory= new void[sizeof(T) * S] = {};
	X.Size = sizeof(T) * S;

	X.Shared->Memory = X.Memory;
	X.Shared->Size = X.Size;
	X.Shared->Shared = X.Shared;

	return *X.Shared;
}

template<class T>
B4edv<T> Recast(const B4ed B,std::intmax_t Pos=0) {

	B4edv<T> R;
	R.Memory=reinterpret_cast<T>(B.Shared->Memory + Pos);
	R.Size = B.Size / sizeof(T);


	return R;
}

int main() {
	B4ed B = NEW<int>(16);

	auto e = Recast<char>(B, 6);


}





