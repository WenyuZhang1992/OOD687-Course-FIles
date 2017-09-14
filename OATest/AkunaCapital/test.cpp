#include <iostream>

template <typename Derived>
struct Comparable {

	bool operator==(const Comparable<Derived>& c) const noexcept {
		const Derived& d1 = static_cast<const Derived&>(c);
		const Derived& d2 = static_cast<const Derived&>(*this);
		return d1.value == d2.value;
	}

	bool operator!=(const Comparable<Derived>& c) const noexcept {
		const Derived& d1 = static_cast<const Derived&>(c);
		const Derived& d2 = static_cast<const Derived&>(*this);
		return d1.value != d2.value;
	}

	bool operator>(const Comparable<Derived>& c) const noexcept {
		const Derived& d1 = static_cast<const Derived&>(c);
		const Derived& d2 = static_cast<const Derived&>(*this);
		return d1.value>d2.value;
	}

	bool operator<=(const Comparable<Derived>& c) const noexcept {
		const Derived& d1 = static_cast<const Derived&>(c);
		const Derived& d2 = static_cast<const Derived&>(*this);
		return d1.value <= d2.value;
	}

	bool operator>=(const Comparable<Derived>& c) const noexcept {
		const Derived& d1 = static_cast<const Derived&>(c);
		const Derived& d2 = static_cast<const Derived&>(*this);
		return d1.value >= d2.value;
	}
};