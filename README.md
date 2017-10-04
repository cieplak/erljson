erljson
======

Json functions for Erlang/OTP implemented as C++ NIFs.

example usage
-------------

Just add it to your rebar.config

```
{deps, [
  ...
  {erljson, {git, "https://github.com/cieplak/erljson.git", {branch, "master"}}},
  ...
```

and fire up a shell

```
$ rebar3 shell

1> Csv = json:to_csv("").
<<"">>

```

supported operating systems
---------------------------

FreeBSD.

Modify line 1 ("`INCLUDES = ...`") in `c_src/Makefile` to point to your C++ headers if it doesn't
compile.
