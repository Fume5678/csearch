//
// Created by fumedesk on 14.06.23.
//

#include "testmain.h"

#include <clocale>
#include <codecvt>
#include <iostream>

TEST_CASE("utf-8 in string"){
  std::setlocale(LC_ALL, "en_US.UTF-8");
  std::string locale = "абвгд";

  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
  std::wstring w_locale = converter.from_bytes(locale.data());

  std::cout << locale.size() << std::endl;

  if( locale.size() != 12){
    FAIL();
  }

  if(!(w_locale[1] > L'а' && w_locale[1] < L'в')){
    FAIL();
  } 
  if(w_locale[1] != L'б'){
    FAIL();
  }

  std::string locale_3 = "一丁丂七丄丅";
  std::cout << std::dec << locale_3.size() << std::endl;

  if(locale.size() != 15){
    FAIL();
  }
  w_locale = converter.from_bytes(locale_3.data());


  if(!(w_locale[1] > L'一' && w_locale[1] < L'丂')){
    FAIL();
  }
  if(w_locale[1] != L'丁'){
    FAIL();
  }
}