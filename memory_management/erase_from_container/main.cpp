#include<deque>
#include<memory>
#include<iostream>
class MyClass{
  public:
    MyClass(int id): _id(id){}
    ~MyClass(){
      std::cout << "MyClass destructor this= " << this << "; _id=" << _id << std::endl;
    }
    int id() const {return _id;}
  private:
    int _id;
};
int main(){
  std::shared_ptr<MyClass> sp = std::make_shared<MyClass>(1);
  std::shared_ptr<MyClass> sp2 = sp;
  MyClass* raw_sp = sp.get();
  std::unique_ptr<MyClass> up = std::make_unique<MyClass>(2);
  MyClass* raw_up = up.get();
  std::deque<std::shared_ptr<MyClass>> q_sp{std::move(sp)};
  std::deque<std::unique_ptr<MyClass>> q_up;
  q_up.emplace_back(std::move(up));
  std::cout << "sp.get() = " << sp.get()<< std::endl;
  std::cout << "raw_sp = " << raw_sp << std::endl;
  for (auto it = q_sp.begin(); it != q_sp.end();){
    std::cout<< "it->get() = " << it->get() << std::endl;
    q_sp.erase(it);
  }
  std::cout << "Iteration over q_sp terminates" << std:: endl;
  std::cout << "up.get() = " << up.get()<< std::endl;
  std::cout << "raw_up = " << raw_up << std::endl;
  for (auto it = q_up.begin(); it != q_up.end();){
    std::cout<< "it->get() = " << it->get() << std::endl;
    q_up.erase(it);
  }
  std::cout << "Iteration over q_up terminates" << std:: endl;
  std::cout << "\nmain is ready to return"<< std::endl;
  return 0;
}

