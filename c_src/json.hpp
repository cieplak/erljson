#pragma once
#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include <jsoncons/json.hpp>

using jsoncons::ojson;
using std::string;
using std::vector;

namespace json {

  namespace detail {
    static inline string join(vector<string> values, const string delimiter = ",") {
      std::stringstream row;
      std::copy(values.begin(),
                values.end() - 1,
                std::ostream_iterator<string>(row, delimiter.c_str()));
      row << values.back();
      return row.str();
    }
  }

  static ojson parse(string input) {
    return ojson::parse(input);
  }

  static string csv(ojson records) {
    std::ostringstream buffer;
    vector<string> headers;
    if (records.size() == 0) return "";
    auto first = records[0];
    for (const auto& kv : first.object_range())
      headers.push_back(kv.key());
    buffer << detail::join(headers) << "\n";
    for (auto record : records.array_range()) {
      vector<string> values;
      for (const auto& kv : record.object_range())
        values.push_back(kv.value().as<string>());
      buffer << detail::join(values) << "\n";
    }
    return buffer.str();
  }

};
