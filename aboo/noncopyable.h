#ifndef __ABOO_NONCOPYABLE_H__
#define __ABOO_NONCOPYABLE_H__

namespace aboo {
class Noncopyable {
public:
	Noncopyable() = default;
	~Noncopyable() = default;
	Noncopyable(const Noncopyable&) = delete;
	Noncopyable& operator=(const Noncopyable&) = delete;
};
}

#endif
