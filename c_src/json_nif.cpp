#include <iostream>
#include <string>
#include <vector>

#include "erl_nif.h"

#include "json.hpp"

using std::string;

static ERL_NIF_TERM
to_csv_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
  ErlNifBinary input, output;

  if (argc == 1) {
    if (enif_inspect_iolist_as_binary(env, argv[0], &input)) {
      if (input.size > 0) {
        std::vector<unsigned char> input_vector;
        for (int i = 0; i < input.size; i++)
          input_vector.push_back(input.data[i]);
        std::string raw_json(input_vector.begin(), input_vector.end());
        auto parsed_json = json::parse(raw_json);
        auto csv = json::csv(parsed_json);
        enif_alloc_binary(csv.length(), &output);
        const char* out = csv.c_str();
        for (int i = 0; i < csv.length(); i++)
          output.data[i] = out[i];
        return enif_make_binary(env, &output);
      };
    };
  };
  return enif_make_badarg(env);
}

static ErlNifFunc nif_funcs[] = {
  {"to_csv", 1, to_csv_nif}
};

ERL_NIF_INIT(json, nif_funcs, NULL, NULL, NULL, NULL)
