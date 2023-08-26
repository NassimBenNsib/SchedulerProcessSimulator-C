ALGORITHMS_FILES = $(wildcard ./algorithms/*.c)
COMPILED_ALGORITHMS_FILES = $(ALGORITHMS_FILES:.c=)

all : show_starting_message delete_all_old_debuged_files debugging_all_files add_execution_premission_to_all_files show_ending_message

show_starting_message : 
	@setterm -foreground yellow -bold on
	@echo "\nInfo : \"If you don't executed as admin, you must enter your password to compile well necessary all files\""
	@read -p "Press Enter key to continue ..." input
	@setterm -foreground green -bold on
	@echo "\n\n======================= Start Of Making =======================\n\n"

delete_all_old_debuged_files :
	rm -rf ./debugging/*
	
debugging_all_files : $(COMPILED_ALGORITHMS_FILES)
	gcc  main.c -o ./debugging/start 
	mkdir ./debugging/algorithms
	mv ./algorithms/*[^.][^c] ./debugging/algorithms || echo ""

add_execution_premission_to_all_files : .
	sudo chmod -R +x ./debugging/*

show_ending_message : 
	@echo "\n\n======================= End Of Making =======================\n\n"

%.o : ./algorithms/%.c
	gcc pkg-config --cflags gtk+-3.0 -o $(COMPILED_ALGORITHMS_FILES) $(ALGORITHMS_FILES) pkg-config --libs gtk+-3.0

