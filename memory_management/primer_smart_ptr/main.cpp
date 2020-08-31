#include<memory>
class cb{
  public:
    int id;
};
int main (){
  std::unique_ptr<cb> p;
  return 0;
}
