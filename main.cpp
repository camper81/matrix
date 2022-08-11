#include <vector>
#include <map>

template<typename T, T VALUE>
struct Element{
    size_t x;
    size_t y;
    T value = VALUE;
    bool operator==(T other) {
        return other == value;
    }
    operator std::tuple<size_t, size_t, T>() {
        return {x, y, value};
    }
};

template<typename T, T VALUE>
class Matrix{
    std::map<size_t, std::map<size_t, Element<T, VALUE>>> adressMap_;
    size_t occupied_;
public:
    Matrix(){

    }
    auto operator[](size_t index){
        return adressMap_[index];
    };
    size_t size() const {
        return occupied_;
    }

};

int main(){
    Matrix<int, -1> matrix;
    auto a = matrix[0][0];
    for(auto& c: matrix){

    }
}
