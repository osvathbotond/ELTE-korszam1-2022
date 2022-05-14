#include <vector>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <type_traits>

template <class T>
class Matrix {
    public:
        std::vector<T> data;

    Matrix() = default;
    Matrix(Matrix const&) = default;
    Matrix(Matrix &&) = default;

    ~Matrix() = default;

    Matrix(std::initializer_list<T> const& values) : data{values} {
        int size = values.size();
        int size_sqrt = (int)std::sqrt(size);
        if(size_sqrt * size_sqrt != size) {
            throw std::length_error("The matrix must be square!");
        }
    }
    Matrix<T>& operator=(Matrix const&) = default;
    Matrix<T>& operator=(Matrix &&) = default;

    Matrix(int n) {
        this->data.resize(n*n);
    }

    size_t elements() const {
        return this->data.size();
    }

    size_t n() const {
        return (size_t)std::sqrt(this->elements());
    }

    template<class t>
    auto operator+(Matrix<t> const& other) const{
        if(this->elements() != other.elements()) {
            throw std::length_error("The matrix shapes are not compatible!");
        }
        using type = typename std::remove_const<decltype(this->data[0] + other.data[0])>::type;
        auto res = Matrix<type>();
        res.data.resize(this->elements());

        std::transform(this->data.begin(), this->data.cend(), other.data.begin(), res.data.begin(), std::plus<type>());

        return res;
    }

    template<class t>
    auto operator-(Matrix<t> const& other) const {
        if(this->elements() != other.elements()) {
            throw std::length_error("The matrix shapes are not compatible!");
        }
        using type = typename std::remove_const<decltype(this->data[0] - other.data[0])>::type;
        auto res = Matrix<type>();
        res.data.resize(this->elements());

        std::transform(this->data.begin(), this->data.cend(), other.data.begin(), res.data.begin(), std::minus<type>());

        return res;
    }

    template<class t>
    auto operator*(Matrix<t> const& other) {
        if(this->elements() != other.elements()) {
            throw std::length_error("The matrix shapes are not compatible!");
        }
        using type = typename std::remove_const<decltype(this->data[0] * other.data[0])>::type;
        auto res = Matrix<type>();
        res.data.resize(this->elements());

        // The index in the result array.
        // I think it's faster to always increment
        // than to calculate it every time.
        size_t position = 0;
        size_t n = this->n();

        // A = BC
        // Aij = BikCkj
        for(size_t i = 0; i < n; i++) {
            for(size_t j = 0; j < n; j++) {
                T element = 0;
                for(size_t k = 0; k < n; k++) {
                    element += this->operator()(i, k) * other(k, j);
                }
                res.data[position] = element;
                position++;
            }
        }

        return res;
    }

    T trace() {
        size_t n = this->n();
        size_t position = 0;

        T res;

        for(size_t i = 0; i < n; i++) {
            res += this->data[position];
            position += n + 1;
        }

        return res;
    }

    T operator[](size_t ind) {
        if(ind >= this->elements()) {
            throw std::out_of_range("Index out of range!");
        }
        return this->data[ind];
    }

    T operator[](size_t ind) const {
        if(ind >= this->elements()) {
            throw std::out_of_range("Index out of range!");
        }
        return this->data[ind];
    }

    T operator()(size_t i, size_t j) {
        size_t n = this->n();
        if(i >= n or j >= n) {
            throw std::out_of_range("Index out of range!");
        }
        auto ind = i * n + j;
        return this->data[ind];
    }

    T operator()(size_t i, size_t j) const {
        size_t n = this->n();
        if(i >= n or j >= n) {
            throw std::out_of_range("Index out of range!");
        }
        auto ind = i * n + j;
        return this->data[ind];
    }

    Matrix<T> transpose() {
        auto res = Matrix<T>();
        res.data.resize(this->elements());

        // The index in the result array.
        // I think it's faster to always increment
        // than to calculate it every time.
        size_t position = 0;
        size_t n = this->n();

        // A = B.T
        // Aij = Bji
        for(size_t j = 0; j < n; j++) {
            for(size_t i = 0; i < n; i++) {
                res.data[position] = this->operator()(i, j);
                position++;
            }
        }

        return res;
    }

    template<typename t>
    auto operator/(t other) const{
        using type = typename std::remove_const<decltype(other * (this->data[0]))>::type;

        auto res = Matrix<type>();
        res.data.resize(this->elements());

        std::transform(this->data.begin(), this->data.end(), res.data.begin(), [other](auto a) {return a/other;});

        return res;
    }

};

template<class T>
auto& operator<<(std::ostream& o, Matrix<T> const& mat) {
    // The index in the result array.
    // I think it's faster to always increment
    // than to calculate it every time.
    size_t position = 0;
    size_t n = mat.n();
    for(size_t i = 0; i < n; i++) {
        for(size_t j = 0; j < n-1; j++) {
            o << mat.data[position] << " ";
            position++;
        }
        o << mat.data[position] << "\n";
        position++;
    }
    return o;
}

// Doing the && operators with 1 class only,
// because of possible differences in memory sizes.
template<class T>
auto&& operator+(Matrix<T>&& mat1, Matrix<T> const& mat2) {
    if(mat1.elements() != mat2.elements()) {
        throw std::length_error("The matrix shapes are not compatible!");
    }

    std::transform(mat1.data.begin(), mat1.data.end(), mat2.data.begin(), mat1.data.begin(), std::plus<T>());

    return std::move(mat1);
}

template<class T>
auto&& operator+(Matrix<T> const& mat1, Matrix<T>&& mat2) {
    if(mat1.elements() != mat2.elements()) {
        throw std::length_error("The matrix shapes are not compatible!");
    }

    std::transform(mat1.data.begin(), mat1.data.end(), mat2.data.begin(), mat2.data.begin(), std::plus<T>());

    return std::move(mat2);
}

template<class T>
auto&& operator+(Matrix<T>&& mat1, Matrix<T> const&& mat2) {
    if(mat1.elements() != mat2.elements()) {
        throw std::length_error("The matrix shapes are not compatible!");
    }

    std::transform(mat1.data.begin(), mat1.data.end(), mat2.data.begin(), mat1.data.begin(), std::plus<T>());

    return std::move(mat1);
}

template<class T>
auto&& operator-(Matrix<T>&& mat1, Matrix<T> const& mat2) {
    if(mat1.elements() != mat2.elements()) {
        throw std::length_error("The matrix shapes are not compatible!");
    }

    std::transform(mat1.data.begin(), mat1.data.end(), mat2.data.begin(), mat1.data.begin(), std::minus<T>());

    return std::move(mat1);
}

template<class T>
auto&& operator-(Matrix<T> const& mat1, Matrix<T>&& mat2) {
    if(mat1.elements() != mat2.elements()) {
        throw std::length_error("The matrix shapes are not compatible!");
    }

    std::transform(mat1.data.begin(), mat1.data.end(), mat2.data.begin(), mat2.data.begin(), std::minus<T>());

    return std::move(mat2);
}

template<class T>
auto&& operator-(Matrix<T>&& mat1, Matrix<T> && mat2) {
    if(mat1.elements() != mat2.elements()) {
        throw std::length_error("The matrix shapes are not compatible!");
    }

    std::transform(mat1.data.begin(), mat1.data.end(), mat2.data.begin(), mat1.data.begin(), std::minus<T>());

    return std::move(mat1);
}

template<class T>
auto operator*(Matrix<T> const& mat, T num) {
    auto res = Matrix<T>();
    res.data.resize(mat.elements());

    std::transform(mat.data.begin(), mat.data.end(), res.data.begin(), [num](auto a) {return num*a;});

    return res;
}

template<class T>
auto operator*(T num, Matrix<T> const& mat) {
    auto res = Matrix<T>();
    res.data.resize(mat.elements());

    std::transform(mat.data.begin(), mat.data.end(), res.data.begin(), [num](auto a) {return num*a;});

    return res;
}

template<class T>
auto&& operator*(T num, Matrix<T> && mat) {

    std::transform(mat.data.begin(), mat.data.end(), mat.data.begin(), [num](auto a) {return num*a;});

    return std::move(mat);
}

template<class T>
auto&& operator*(Matrix<T> && mat, T num) {

    std::transform(mat.data.begin(), mat.data.end(), mat.data.begin(), [num](auto a) {return num*a;});

    return std::move(mat);
}

template<class T>
auto&& operator/(Matrix<T> && mat, T num) {

    std::transform(mat.data.begin(), mat.data.end(), mat.data.begin(), [num](auto a) {return a/num;});

    return std::move(mat);
}