#include <list>
#include <map>
#include <iostream>
#include <iomanip>

template<typename T, T DefaultValue = -1>
class Matrix{
public:
    class SubMatrix{
    public:
        struct Element{
            size_t row_ = -1;
            size_t col_ = -1;
            T value_;
            SubMatrix* parent_ = nullptr;
            // Для создания связного списка
            Element* next = nullptr;

            operator T() const{
                return value_;
            }

            void operator=(T value){
                value_ = value;
                // оповещаем родителя, что появился новый элемент у которого есть значение
                parent_->setLastElement(this);
            }
            // Преобразования в кортеж
            std::tuple<size_t, size_t, T> getTuple(){
                return std::tie(row_, col_, value_);
            }
        };

        SubMatrix(Matrix* parent = nullptr): parent_(parent){};

        SubMatrix& operator=(SubMatrix& sub){
            this = sub;
        }

        Element& operator[](size_t col){
            // Проброс номера колонки из предыдущего оператора [] вызванного из Matrix
            size_t row = parent_->last_input_row_;
            // Перебираем подряд все элементы
            for(auto it = elements.begin(), end = elements.end(); it != end; ++it)
                // Если элемент с такой адресацией найден то возвращаем его
                if(it->row_ == row && it->col_ == col)
                    return *it;

            // Если не найден то создаём новый со стандартными значениями(это необходимо если дальее эта ячейка будет
            // использоваться для занесения в неё значений)
            elements.push_back({row, col, DefaultValue, this});
            return elements.back();
        }

        void setLastElement(Element* element){
            // У родителя увеличиваем количество элементов которые имеют значения
            parent_->elements_size_++;
            // Далее заполняем LinkedList у родителя
            if(parent_->elements_ == nullptr){
                // Для первого элемента в списке
                parent_->elements_ = element;
                return;
            }

            auto cur_elem = parent_->elements_;
            while(cur_elem->next)
                cur_elem = cur_elem->next;
            cur_elem->next = element;
        }

        std::list<Element> elements; // Список элементов
        Matrix* parent_;
    };

    SubMatrix& operator[](const size_t& row){
        last_input_row_ = row;
        SubMatrix sub(this);
        submatrix.insert(std::pair(row, sub));
        return submatrix[row];
    }
    std::tuple<size_t, size_t, T> getElement(size_t idx){
        auto cur_elem = elements_;
        while(idx--){
            cur_elem = cur_elem->next;
        }
        return cur_elem->getTuple();
    };
public:
    struct iterator{
        iterator(size_t elem_count, Matrix* parent) : position_(elem_count), parent_(parent) {};
        iterator& operator++(){
            position_++;
            return *this;
        }
        bool operator!=(iterator other){
            return position_ != other.position_;
        }
        auto operator*(){
            return parent_->getElement(position_);
        }
        size_t position_;
        Matrix* parent_;
    };
    iterator begin(){
        return iterator(0, this);
    }
    iterator end(){
        return iterator(elements_size_, this);
    }

    size_t size() const {
        return elements_size_;
    }

    size_t last_input_row_;
    size_t elements_size_ = 0;
    typename SubMatrix::Element* elements_;
    std::map<size_t, SubMatrix> submatrix;
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
    for(int i = 1; i < n - 1; ++i) {
        for(int j = 1; j < n - 1; ++j) {
            std::cout << std::setw(2)<< main_matrix[i][j] << " ";
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