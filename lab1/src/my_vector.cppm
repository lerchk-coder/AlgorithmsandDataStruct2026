export module my_vector;

import std;

template <typename T>
struct is_complex : std::false_type {};

template <typename T>
struct is_complex<std::complex<T>> : std::true_type {};

template <typename T>
inline constexpr bool is_complex_v = is_complex<T>::value;

export template <typename T>
class MyVector {
public:
    static constexpr double epsilon_ = 1e-6;

private:
    T* data_;
    std::size_t size_;

public:
    MyVector(std::size_t size, T fill_value) : size_(size), data_(new T[size]) {
        for (std::size_t i = 0; i < size_; ++i) data_[i] = fill_value;
    }

    MyVector(std::size_t size, T min_val, T max_val) : size_(size), data_(new T[size]) {
        std::random_device rd;
        std::mt19937 gen(rd());
        for (std::size_t i = 0; i < size_; ++i) {
            if constexpr (std::is_integral_v<T>) {
                std::uniform_int_distribution<T> dist(min_val, max_val);
                data_[i] = dist(gen);
            }
            else if constexpr (is_complex_v<T>) {
                using RealType = typename T::value_type;
                std::uniform_real_distribution<RealType> dist_real(std::real(min_val), std::real(max_val));
                std::uniform_real_distribution<RealType> dist_imag(std::imag(min_val), std::imag(max_val));
                data_[i] = T(dist_real(gen), dist_imag(gen));
            }
            else {
                std::uniform_real_distribution<T> dist(min_val, max_val);
                data_[i] = dist(gen);
            }
        }
    }

    ~MyVector() { delete[] data_; }

    MyVector(const MyVector& other) : size_(other.size_), data_(new T[other.size_]) {
        for (std::size_t i = 0; i < size_; ++i) data_[i] = other.data_[i];
    }

    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            MyVector temp(other);
            std::swap(data_, temp.data_);
            std::swap(size_, temp.size_);
        }
        return *this;
    }

    MyVector(MyVector&& other) noexcept : data_(other.data_), size_(other.size_) {
        other.data_ = nullptr;
        other.size_ = 0;
    }

    MyVector& operator=(MyVector&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            other.data_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    std::size_t size() const { return size_; }

    T& operator[](std::size_t index) {
        if (index >= size_) throw std::out_of_range("Индекс выходит за пределы вектора");
        return data_[index];
    }

    const T& operator[](std::size_t index) const {
        if (index >= size_) throw std::out_of_range("Индекс выходит за пределы вектора");
        return data_[index];
    }

    MyVector& operator+=(const MyVector& other) {
        if (size_ != other.size_) throw std::invalid_argument("Размеры векторов должны совпадать для сложения");
        for (std::size_t i = 0; i < size_; ++i) data_[i] += other.data_[i];
        return *this;
    }

    MyVector operator+(const MyVector& other) const {
        MyVector result(*this);
        result += other;
        return result;
    }

    MyVector& operator-=(const MyVector& other) {
        if (size_ != other.size_) throw std::invalid_argument("Размеры векторов должны совпадать для вычитания");
        for (std::size_t i = 0; i < size_; ++i) data_[i] -= other.data_[i];
        return *this;
    }

    MyVector operator-(const MyVector& other) const {
        MyVector result(*this);
        result -= other;
        return result;
    }

    T operator*(const MyVector& other) const {
        if (size_ != other.size_) throw std::invalid_argument("Размеры векторов должны совпадать для скалярного произведения");
        T result{};
        for (std::size_t i = 0; i < size_; ++i) {
            if constexpr (is_complex_v<T>) {
                result += data_[i] * std::conj(other.data_[i]);
            }
            else {
                result += data_[i] * other.data_[i];
            }
        }
        return result;
    }

    MyVector& operator*=(T scalar) {
        for (std::size_t i = 0; i < size_; ++i) data_[i] *= scalar;
        return *this;
    }

    MyVector operator*(T scalar) const {
        MyVector result(*this);
        result *= scalar;
        return result;
    }

    friend MyVector operator*(T scalar, const MyVector& vec) {
        return vec * scalar;
    }

    MyVector& operator/=(T scalar) {
        if (std::abs(scalar) < epsilon_) throw std::invalid_argument("Деление на ноль (скаляр слишком мал)");
        for (std::size_t i = 0; i < size_; ++i) data_[i] /= scalar;
        return *this;
    }

    MyVector operator/(T scalar) const {
        MyVector result(*this);
        result /= scalar;
        return result;
    }

    bool operator==(const MyVector& other) const {
        if (size_ != other.size_) return false;
        for (std::size_t i = 0; i < size_; ++i) {
            if (std::abs(data_[i] - other.data_[i]) > epsilon_) return false;
        }
        return true;
    }

    bool operator!=(const MyVector& other) const {
        return !(*this == other);
    }


    friend std::ostream& operator<<(std::ostream& os, const MyVector& vec) {
        os << "(";
        for (std::size_t i = 0; i < vec.size_; ++i) {
            os << vec.data_[i];
            if (i < vec.size_ - 1) os << ", ";
        }
        os << ")";
        return os;
    }
};