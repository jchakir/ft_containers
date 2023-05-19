# *********************************************************************
# Created by Jaouad Chakir (jchakir@student.1337.ma) on 8/31/22.
# Copyright (c) 1337.ma(@1337FIL) . All rights reserved.
# *********************************************************************

NS = ft
comp = c++
flags = -Wall -Wextra -Werror -std=c++98# -g3 -fsanitize=address
name = program

cpp_files = main.cpp

obj_files = $(cpp_files:%.cpp=%.obj)

all: $(name)

$(name): $(obj_files)
	$(comp) $(flags) $(obj_files) -o $(name)

%.obj: %.cpp
	$(comp) $(flags) -D ns=$(NS) -c $< -o $@

clean:
	rm -rf $(obj_files)

fclean: clean
	rm -rf $(name)

re: fclean all

clean_diff:
	rm -rf std.log ft.log

diff:
	@diff std.log ft.log

run:
	./$(name) > $(NS).log
