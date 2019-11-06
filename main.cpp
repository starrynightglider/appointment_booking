#include <iostream>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/ostreamwrapper.h"

using namespace rapidjson;

int main()
{
  // 1. Parse a JSON string into DOM.
  const char *json = "{\"project\":\"rapidjson\",\"stars\":10}";
  Document d;
  d.Parse(json);

  // 2. Modify it by DOM.
  Value &s = d["stars"];
  s.SetInt(s.GetInt() + 1);

  // 3. Stringify the DOM
  StringBuffer buffer;
  Writer<StringBuffer> writer(buffer);
  d.Accept(writer);

  // Output {"project":"rapidjson","stars":11}
  std::cout << buffer.GetString() << std::endl;
  {
    std::ifstream ifs{R"(orders.json)"};
    if (!ifs.is_open())
    {
      std::cerr << "Cannot open file" << std::endl;
      return 0;
    }
    IStreamWrapper isw{ifs};
    Document doc;
    doc.ParseStream(isw);
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    doc.Accept(writer);

    if (doc.HasParseError())
    {
      std::cout << "Error: " << doc.GetParseError() << std::endl;
      std::cout << "Offset: " << doc.GetErrorOffset() << std::endl;
    }
    std::cout << buffer.GetString() << std::endl;
  }
  return 0;
}