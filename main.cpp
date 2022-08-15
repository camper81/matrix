#include <vector>
#include <map>
#include <cassert>
#include <iostream>
#include <map>
#include <memory>

template<typename T, T>
class Matrix;

template<typename T, T DefaultValue>
class SubMatrix {
public:
    class MatrixElement {
    public:
        MatrixElement(){
            data = DefaultValue;
            idx = -1;
            matrix_pointer = nullptr;
        };
        MatrixElement(T data_, int id_, Matrix<T, DefaultValue> *matrix_ptr_) :
                data{data_}, idx{id_}, matrix_pointer(matrix_ptr_) {

        }

        operator T() const {
            return data;
        }

        MatrixElement& operator=(const T& rhs) {
            value = true;
            data = rhs;

            if (data != DefaultValue)
                matrix_pointer->move_to_known(idx);
//            else
//                matrix_pointer->move_to_unknown(idx);

            return *this;
        }

        T item() const {
            return data;
        }

        bool operator!=(const T rhs) const {
            return data != rhs;
        }

        bool operator!=(const MatrixElement rhs) const {
            return data != rhs.data;
        }

    private:
        T data;
    public:
        void setData(T data) {
            MatrixElement::data = data;
        }

        void setMatrixPointer(SubMatrix<T, DefaultValue> *matrixPointer) {
            matrix_pointer = matrixPointer;
        }

        void setIdx(int idx) {
            MatrixElement::idx = idx;
        }

    private:
        SubMatrix<T, DefaultValue> *matrix_pointer;
        int idx;
    public:
        bool isValue() const {
            return value;
        }

    private:
        bool value = false;
    };


    MatrixElement& operator[](const int idx) {
        if (elements.count(idx) == 0) {
            if (elements.count(idx) > 0)
                return elements.at(idx);
////            MatrixElement element(DefaultValue, idx, this);
//            other[idx].setData(DefaultValue);
//            other[idx].setMatrixPointer(this);
//            other[idx].setIdx(idx);
////            return elements[idx];
//              return other[idx];
        }
        return tempElement;
    }

    size_t size() const {
        return elements.size();
    }

    SubMatrix& operator=(const T& rhs) {
        if (this == &rhs)
            return *this;
        elements = rhs.elements;
        return *this;
    }

    std::tuple<int, T> get(int elem_num) const {
        int i = 0;
        for (const auto&[key, value]:elements) {
            if (i == elem_num) {
                return std::make_tuple(key, T(value));
            } else {
                i++;
            }
        }
        throw std::out_of_range("No such element");
    }

private:
    std::map<int, MatrixElement> elements;
    std::map<int, MatrixElement> other;
    MatrixElement tempElement;
//    std::map<int, MatrixElement> elements_temp;

    void move_to_known(int idx) {
//        if (elements_temp.count(idx) > 0) {
            elements.insert(std::make_pair(idx, elements.at(idx)));
//            elements_temp.erase(idx);
//        }
    }

//    void move_to_unknown(int idx) {
//        if (elements.count(idx) > 0) {
//            elements.erase(idx);
//        }
//    }

};

template<typename T, T DefaultValue>
class Matrix {
public:
    Matrix() = default;

    size_t size() const {
        size_t result = 0;
        for (const auto&[key, value]:elements) {
            result += value.size();
        }
        return result;
    }



    SubMatrix<T, DefaultValue>& operator[](const int idx) {
        return elements[idx];
    }

    Matrix& operator=(const T& rhs) {
        if (this == &rhs)
            return *this;
        elements = rhs.elements;
        return *this;
    }

    decltype(auto) get(size_t elem_num) const {
        int i = 0;
        for (const auto&[key, value]:elements) {
            size_t cur_size = value.size();
            if (i + cur_size > elem_num) {
                return std::tuple_cat(std::make_tuple(key), value.get(elem_num - i));
            } else {
                i += cur_size;
            }
        }
        throw std::logic_error("no element");
    }

    class iterator {
    public:
        using value_type = Matrix;
        using pointer = Matrix *;

        iterator(Matrix& parent, int elem_num_) : parent_(parent), elem_num(elem_num_) {}

        iterator operator++() {
            iterator i = *this;
            elem_num++;
            return i;
        }

        decltype(auto) operator*() { return parent_.get(elem_num); }

        bool operator!=(const iterator& rhs) { return elem_num != rhs.elem_num; }

    private:
        int elem_num;
        Matrix& parent_;
    };

    iterator begin() {
        return iterator(*this, 0);
    }

    iterator end() {
        return iterator(*this, size());
    }
private:
    std::map<int, SubMatrix<T, DefaultValue>> elements;
};

int main() {
    Matrix<int, -1> main_matrix;
    const int n = 10;
    // fill main diagonal
    for(int i = 0; i < n; i++) {
        main_matrix[i][i] = i;
    }

    // fill counter diagonal
    for(int i = n - 1; i >= 0; i--) {
        main_matrix[i][n - i - 1] = i;
    }
    std::cout << "Matrix:" << std::endl;
    for(int i = 1; i < n-1; i++) {
        for(int j = 1; j < n-1; j++) {
            if(j > 1) std::cout << " ";
            std::cout << main_matrix[i][j];
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Matrix cells: " << main_matrix.size() << std::endl;

    std::cout << std::endl;
    std::cout << "Matrix elements:" << std::endl;
    for(auto elem: main_matrix)
    {
        int i, j, value;
        std::tie(i, j, value) = elem;
        std::cout << "matrix[" << i << "][" << j << "] = " << value << std::endl;
    }
    std::cout << "done" << std::endl;

    return 0;
}