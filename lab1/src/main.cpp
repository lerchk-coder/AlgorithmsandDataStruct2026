import std;
import my_vector;

double calculate_triangle_area(const MyVector<double>& a, const MyVector<double>& b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("Размеры векторов должны совпадать");
    }
    if (a.size() < 2) {
        throw std::invalid_argument("Векторы должны быть как минимум двумерными для образования треугольника");
    }

    double dot_aa = a * a;
    double dot_bb = b * b;
    double dot_ab = a * b;

    double mag_ab_sq = dot_ab * dot_ab;
    double term = dot_aa * dot_bb - mag_ab_sq;

    if (term < 0.0) term = 0.0;

    return 0.5 * std::sqrt(term);
}

int main() {
    std::system("chcp 65001 > nul");
    std::cout << "=== ЛАБОРАТОРНАЯ 1: ВЕКТОРЫ И ЗАДАЧА 5 ===\n" << std::endl;

    try {
        std::cout << "--- Целочисленные векторы ---" << std::endl;
        MyVector<int> v_int1(3, 2);
        MyVector<int> v_int2(3, 1, 5);

        std::cout << "v_int1: " << v_int1 << std::endl;
        std::cout << "v_int2 (случайный): " << v_int2 << std::endl;
        std::cout << "v_int1 + v_int2 = " << (v_int1 + v_int2) << std::endl;
        std::cout << "v_int1 == v_int2? " << (v_int1 == v_int2 ? "Да" : "Нет") << std::endl;

        std::cout << "\n--- Вещественные векторы (double) ---" << std::endl;
        MyVector<double> v_double1(3, 1.5);
        MyVector<double> v_double2(3, 1.5);

        std::cout << "v_double1: " << v_double1 << std::endl;
        std::cout << "Скалярное произведение: " << (v_double1 * v_double2) << std::endl;
        std::cout << "v_double1 * 2.0 = " << (v_double1 * 2.0) << std::endl;
        std::cout << "2.0 * v_double1 = " << (2.0 * v_double1) << std::endl;
        std::cout << "v_double1 / 2.0 = " << (v_double1 / 2.0) << std::endl;

        std::cout << "\n--- Комплексные векторы ---" << std::endl;
        using Complex = std::complex<double>;
        MyVector<Complex> v_comp1(2, Complex(1.0, 1.0));
        MyVector<Complex> v_comp2(2, Complex(1.0, -1.0));

        std::cout << "v_comp1: " << v_comp1 << std::endl;
        std::cout << "v_comp2: " << v_comp2 << std::endl;

        Complex dot_comp = v_comp1 * v_comp2;
        std::cout << "Скалярное произведение: " << dot_comp.real() << " + " << dot_comp.imag() << "i" << std::endl;

        std::cout << "\n--- Проверка исключений ---" << std::endl;
        try {
            MyVector<int> small_v(2, 1);
            MyVector<int> large_v(3, 1);
            auto err = small_v + large_v;
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Поймано исключение: " << e.what() << std::endl;
        }
        try {
            std::cout << v_int1[10] << std::endl;
        }
        catch (const std::out_of_range& e) {
            std::cout << "Поймано исключение: " << e.what() << std::endl;
        }

        std::cout << "\n--- Задача 5: Площадь треугольника ---" << std::endl;
        MyVector<double> vec_a(2, 0.0);
        vec_a[0] = 3.0;

        MyVector<double> vec_b(2, 0.0);
        vec_b[1] = 4.0;

        std::cout << "Вектор OA: " << vec_a << std::endl;
        std::cout << "Вектор OB: " << vec_b << std::endl;
        std::cout << "Площадь треугольника OAB: " << calculate_triangle_area(vec_a, vec_b) << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Непредвиденное исключение: " << e.what() << std::endl;
    }

    return 0;
}