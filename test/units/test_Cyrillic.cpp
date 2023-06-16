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
  std::cout << std::hex << (int)locale[0] << std::endl;
  std::cout << std::hex << (int)locale[1] << std::endl;
  std::cout << std::hex << (int)locale[2] << std::endl;
  std::cout << std::hex << (int)locale[3] << std::endl;

  if(w_locale[1] > L'а' && w_locale[1] < L'в'){
    std::cout << "Good";
  }
  if(w_locale[1] == L'б'){
    std::cout << "Good";
  }

  std::cout << w_locale.size() << std::endl;
  std::cout << std::hex << (int)w_locale[0] << std::endl;
  std::wcout << std::dec << w_locale[0] << std::endl;
  std::wcout << L"фывыфв" << std::endl;
  std::wcout << w_locale << std::endl;

  std::string locale_2 = "abcde";
  std::cout << std::dec << locale_2.size() << std::endl;
  std::cout << std::hex << (int)locale_2[0] << std::endl;
  std::cout << std::hex << (int)locale_2[1] << std::endl;
  std::cout << std::hex << (int)locale_2[2] << std::endl;
  std::cout << std::hex << (int)locale_2[3] << std::endl;

  std::string locale_3 = "一丁丂七丄丅";
  std::cout << std::dec << locale_3.size() << std::endl;
  std::cout << std::hex << (int)locale_3[0] << std::endl;
  std::cout << std::hex << (int)locale_3[1] << std::endl;
  std::cout << std::hex << (int)locale_3[2] << std::endl;
  std::cout << std::hex << (int)locale_3[3] << std::endl;

  w_locale = converter.from_bytes(locale_3.data());
  if(w_locale[1] > L'一' && w_locale[1] < L'丂'){
    std::cout << "Good";
  }
  if(w_locale[1] == L'丁'){
    std::cout << "Good";
  }
}