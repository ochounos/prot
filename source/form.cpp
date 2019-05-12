#include "form.h"
#include <iostream>
#include "type_container.h"
using namespace std;


form::form(const string & path):form(){
  json_reader = make_unique<form_reader>(path);
}

form::form(){
  static int acummulator = 0;
  id = "form" + to_string(acummulator++);
}

form::~form()
{
  cout << "form destroyed" << endl;
}

void form::send_action(std::string action, map<char, string> params)
{
  if (form_map.find(action) != form_map.end())
  {
    form_map[action](params);
  }
  else
  {
    cout << action << " :Does not match. Not provided correct arguments" <<endl;
  }
}

void form::set_path(const string & s){
  const auto & path = s;
  json_reader = make_unique<form_reader>(path);
}

void form::add(map<char,string> params){
  if(params.size() == 0){
    cout << "nothing done" << endl;
    return;
  }
  auto it = setters.end();
  for(auto e: params){
    it = setters.find(e.first);
    if(it != setters.end()){
        setters[e.first](*this,e.second);
    }
  }
}

void test_type_container(){
  type_container<int32_t> thre_two ("INTEGER","32");
  cout << thre_two.value << endl;
  type_container<string> str ("STRING","Lemons are my favourite");
  cout << str.value << endl;
}


