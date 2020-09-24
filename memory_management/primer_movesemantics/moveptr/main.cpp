#include<memory>
#include<vector>
#include<iostream>
class MyData{
  public:
    int data{0};
    MyData(int d): data(d) {std::cout << "MyData constructor " << this << " with value " << data <<std::endl;}
    ~MyData(){
      std::cout << "MyData destructor " << this << "; ";
      std::cout << "data: " << data << std::endl;
    }
};
class MyClass{
  private:
    int _id;
    MyData* _dataptr;
    std::unique_ptr<MyData> _uniqueData;
    std::vector<std::unique_ptr<MyData>> _udatas;
  public:
    MyClass(int id): _id(id){std::cout <<"MyClass constructor " << this << std::endl;}
    MyClass(MyClass &source){
      _id=source.ID();
      _dataptr=source.Data();
      std::cout << "MyClass copy constructor " << this << "; ";
      std::cout << "_id: " << _id << "; ";
      std::cout << "_dataptr: " << _dataptr << std::endl;
    }
    ~MyClass(){
      std::cout << "MyClass destructor "  << this << "  ";
      /*
      if (_dataptr!=nullptr){ 
        std::cout << "  Deleting _dataptr " << _dataptr ;
        delete _dataptr;
      }
      */
      std::cout << std::endl;
    }
    void init_uniqueData(int d){
      _uniqueData = std::make_unique<MyData>(d);
    }
    void init_udatas(std::vector<int> datas){
      std::cout << std::endl;
      std::cout << "MyClass " << this << " initialising _udatas" << std::endl;
      for (auto it = datas.begin(); it!= datas.end(); ++it){
        _udatas.push_back(std::make_unique<MyData>(*it));
      }
      std::cout << std::endl;
    }
    int& ID(){return _id;}
    MyData* Data(){return _dataptr;}
    void SetData(MyData* d){
      std::cout << "MyClass " << this << " setting _dataptr " << d << std::endl;
      _dataptr=d;}
    void SetData(MyData& d){
      std::cout << "MyClass " << this << " setting _dataptr " << &d << std::endl;
      _dataptr=&d;}
    void print_dataptr(){std::cout << "MyClass "<< this << " _dataptr: " << _dataptr << std::endl;}
    void print_uniqueData(){std::cout << "MyClass "<< this << " _uniqueData: " << _uniqueData.get() << std::endl;}
    void print_udatas(){
      std::cout << std::endl;
      std::cout << "MyClass " << this << " _datas: ";
      for (auto it = _udatas.begin(); it!=_udatas.end(); ++it){
        std::cout << (*it).get() << " value: " << (*it)->data << std::endl;
      }
      std::cout << std::endl;
    }
};
int main(){
  MyData mydata(0);
  MyClass class1(1);
  class1.SetData(&mydata);
  class1.print_dataptr();
  class1.init_uniqueData(1);
  class1.print_uniqueData();
  class1.init_udatas(std::vector<int>{3,5});
  MyClass class2(class1);
  class2.print_dataptr();
  class2.init_uniqueData(2);
  class2.print_uniqueData();
  return 0;
}




