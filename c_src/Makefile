INCLUDES = -I /usr/local/include -I jsoncons/include -I include -I /usr/local/lib/erlang/usr/include
STD      = -std=c++1z
CC       = clang++

default: deps json_nif

deps:
	git clone --depth 1 https://github.com/danielaparker/jsoncons.git

json_nif:
	$(CC) $(STD) $(INCLUDES) json_nif.cpp -fpic -shared -o json.so
	cp json.so ../priv/.
