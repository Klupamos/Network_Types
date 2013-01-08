#all: make_gcc make_vs make_mg run
all: make_gcc run_gcc


# The GCC variable section
GCC_COMPILER = g++
GCC_COMPILE_FLAGS = -c -Wall
GCC_LINK_FLAGS = 
GCC_FOLDER = g++/

make_gcc: gcc_folder $(GCC_FOLDER)program.exe

run_gcc:
	./$(GCC_FOLDER)program.exe

gcc_folder:
	-@mkdir -p $(GCC_FOLDER)

$(GCC_FOLDER)program.exe: $(GCC_FOLDER)network_types.o $(GCC_FOLDER)source.o
	$(GCC_COMPILER) $(GCC_LINK_FLAGS) $(GCC_FOLDER)network_types.o $(GCC_FOLDER)source.o -o $(GCC_FOLDER)program.exe

$(GCC_FOLDER)network_types.o: network_types.cpp network_types.h
	$(GCC_COMPILER) $(GCC_COMPILE_FLAGS) network_types.cpp -o $(GCC_FOLDER)network_types.o
	
$(GCC_FOLDER)source.o: source.cpp network_types.h
	$(GCC_COMPILER) $(GCC_COMPILE_FLAGS) source.cpp -o $(GCC_FOLDER)source.o
	




# The Visual Studio variable section
VS_COMPILER = g++
VS_COMPILE_FLAGS = -c -Wall
VS_LINK_FLAGS = 
VS_FOLDER = Visual\ Studios\ 2012/

make_vs: vs_folder $(VS_FOLDER)program.exe

run_vs:
	./$(VS_FOLDER)program.exe
	
vs_folder:
	-@mkdir -p $(VS_FOLDER)

$(VS_FOLDER)program.exe: $(VS_FOLDER)network_types.o $(VS_FOLDER)source.o
	$(VS_COMPILER) $(VS_LINK_FLAGS) $(VS_FOLDER)network_types.o $(VS_FOLDER)source.o -o $(VS_FOLDER)program.exe

$(VS_FOLDER)network_types.o: network_types.cpp network_types.h
	$(VS_COMPILER) $(VS_COMPILE_FLAGS) network_types.cpp -o $(VS_FOLDER)network_types.o
	
$(VS_FOLDER)source.o: source.cpp network_types.h
	$(VS_COMPILER) $(VS_COMPILE_FLAGS) source.cpp -o $(VS_FOLDER)source.o





# The Migwn variable section
MG_COMPILER = g++
MG_COMPILE_FLAGS = -c -Wall
MG_LINK_FLAGS = 
MG_FOLDER = Migwin/

make_mg: mg_folder $(MG_FOLDER)program.exe

run_mg:
	./$(MG_FOLDER)program.exe
	
mg_folder:
	-@mkdir -p $(MG_FOLDER)

$(MG_FOLDER)program.exe: $(MG_FOLDER)network_types.o $(MG_FOLDER)source.o
	$(MG_COMPILER) $(MG_LINK_FLAGS) $(MG_FOLDER)network_types.o $(MG_FOLDER)source.o -o $(MG_FOLDER)program.exe

$(MG_FOLDER)network_types.o: network_types.cpp network_types.h
	$(MG_COMPILER) $(MG_COMPILE_FLAGS) network_types.cpp -o $(MG_FOLDER)network_types.o

$(MG_FOLDER)source.o: source.cpp network_types.h
	$(MG_COMPILER) $(MG_COMPILE_FLAGS) source.cpp -o $(MG_FOLDER)source.o


	
# The global commands
run: run_gcc run_vs run_mg

clean:
	rm -rf $(GCC_FOLDER) $(VS_FOLDER) $(MG_FOLDER) 
