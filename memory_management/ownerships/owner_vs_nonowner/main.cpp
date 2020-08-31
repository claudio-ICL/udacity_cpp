#include<memory>
#include<vector>
#include<iostream>
class MyClass{
  private:
    std::vector<std::shared_ptr<int>> owned;
    std::vector<std::weak_ptr<int>> nonowned;
    std::vector<std::shared_ptr<int>> exclowned;
    std::weak_ptr<int> single_nonowned;
  public:
    MyClass(){std::cout<< "MyClass constructor " << this << std::endl;}
    ~MyClass(){std::cout<< "MyClass desctructor "<< this << std::endl;}
    void set_owned(std::vector<int>& data){
      for (auto it = data.begin(); it != data.end(); ++it){ owned.push_back(std::make_shared<int>(*it)); }
    }
    void set_nonowned(std::vector<std::shared_ptr<int>> &data){
      for (auto it = data.begin(); it != data.end(); ++it){
        nonowned.push_back(*it);
      }
    }
    void set_exclusive_owned(std::unique_ptr<int> && data){
      exclowned.push_back(std::move(data));
    }
    void set_exclusive_owned(std::vector<int> &data){
      for (auto it = data.begin(); it!= data.end(); ++it){
        set_exclusive_owned(std::move(std::make_unique<int>(*it)));
      }
    }
    void set_single_nonowned(std::shared_ptr<int>& data){
      single_nonowned = data;
    }
    std::vector<std::shared_ptr<int>> &get_owned(){return owned;}
    std::vector<std::shared_ptr<int>> &get_exclowned(){return exclowned;}
    void print_this(){std::cout << "MyClass " << this << " ";}
    void print_owned(){
      std::cout << "MyClass " << this << " owned: " << std::endl;
      for (auto it = owned.begin(); it != owned.end(); ++it){
        std::cout << (*it).get() << "  " << **it << std::endl;
      }
    }
    void print_nonowned(){
      std::cout << "MyClass " << this << " nonowned: " << std::endl;
      for (auto it = nonowned.begin(); it != nonowned.end(); ++it){
        auto ptr = (*it).lock();
        std::cout << ptr.get() << "  " << *ptr << std::endl;
      }
    }
    void print_exclowned(){
      std::cout << "MyClass " << this << " exclowned: " << std::endl;
      for (auto it = exclowned.begin(); it != exclowned.end(); ++it){
        std::cout << (*it).get() << "  " << **it << std::endl;
      }
    }
    void print_single_nonowned(){
      std::cout << "MyClass " << this << " single_nonowned: " << std::endl;
      auto ptr = single_nonowned.lock();
      std::cout << ptr.get() << "  " << *ptr << std::endl;
    }
    void print(){
      print_owned();
      print_nonowned();
      print_exclowned();
      print_single_nonowned();
    }
};
int main(){
  std::vector<int> data1{0,1,2};
  std::vector<int> data2{3,4,5};
  std::vector<int> excldata1{0,-1,-2};
  std::vector<int> excldata2{-3,-4,-5};
  MyClass myclass1;
  myclass1.set_owned(data1);
  myclass1.set_exclusive_owned(excldata1);
  MyClass myclass2;
  myclass2.set_owned(data2);
  myclass2.set_exclusive_owned(excldata2);
  {
  myclass1.set_nonowned(myclass2.get_owned());
  myclass2.set_nonowned(myclass1.get_owned());
  }
  {
  myclass1.set_single_nonowned(myclass2.get_owned().front());
  myclass2.set_single_nonowned(myclass1.get_owned().front());
  }
  std::cout << "____ myclass1 ____" << std::endl;
  myclass1.print();
  std::cout << "____ myclass2 ____" << std::endl;
  myclass2.print();
  return 0;
}



      

