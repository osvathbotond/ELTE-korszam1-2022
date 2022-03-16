#include <stdexcept>
#include <cmath>

template <class T>
class Vector2 {
    public:
        T x, y;

        Vector2(T x, T y) {
            this->x = x;
            this->y = y;
        }

        template<class t>
        auto operator+(Vector2<t> const& other) {
            using type = typename std::remove_const<decltype(this->x + other.x)>::type;
            return Vector2<type>(this->x + other.x, this->y + other.y);
        }

        auto& operator+=(Vector2<T> const& other) {
            this->x += other.x;
            this->y += other.y;
            return *this;
        }

        template<class t>
        auto operator-(Vector2<t> const& other) {
            using type = typename std::remove_const<decltype(this->x - other.x)>::type;
            return Vector2<type>(this->x - other.x, this->y - other.y);
        }

        auto& operator-=(Vector2<T> const& other) {
            this->x -= other.x;
            this->y -= other.y;
            return *this;
        }

        template<class t>
        auto dot(Vector2<t> const& other) {
            return this->x * other.x + this->y * other.y;
        }

        template<class t>
        auto cross(Vector2<t> const& other) {
            return (this->x) * (other.y) -(this->y) * (other.x);
        }

        T normSquared() {
            return this->dot(*this);
        }

        double norm() {
            return std::sqrt(this->normSquared());
        }

        template<typename t>
        auto operator*(t other) {
            using type = typename std::remove_const<decltype(other * (this->x))>::type;
            return Vector2<type>(other * (this->x), other * (this->y));
        }

        template<typename t>
        auto& operator*=(t other) {
            this->x *= other;
            this->y *= other;
            return *this;
        }

        template<typename t>
        auto operator/(t other) {
            using type = typename std::remove_const<decltype((this->x) / other)>::type;
            return Vector2<type>((this->x) / other, (this->y) / other);
        }

        template<typename t>
        auto& operator/=(t other) {
            this->x /= other;
            this->y /= other;
            return *this;
        }

        auto normalized() {
            return *this / this->norm();
        }

        Vector2<T> orthogonal() {
            return Vector2<T>(-this->y, this->x);
        }

        T& operator[](size_t ind) {
            if(ind == 0) {
                return this->x;
            } else if(ind == 1) {
                return this->y;
            } else {
                throw std::out_of_range("The possible indices are 0 and 1!");
            }
        }
};

template<class T1, class T2>
auto operator*(T1 lhs, Vector2<T2> const& rhs ){
    using type = typename std::remove_const<decltype(lhs * (rhs.x))>::type;
    return Vector2<type>(lhs * (rhs.x), lhs * (rhs.y));
}
template<class T>
auto& operator<<(std::ostream& o, Vector2<T> const& vec){
    o << "(" << vec.x << ", " << vec.y << ")";
    return o;
}

template<class T>
auto& operator>>(std::istream& i, Vector2<T>& vec){
    i >> vec.x;
    i >> vec.y;
    return i;
}