
# Coded by AlysonBelle

executable = synchronize

sources_directory = sources/

handshake_directory = sources/handshaking/

objects_directory = objects/

alylibc = alylibc/

alylibc_a = lib.a

handshake_list = handshake.c \
		deserialize_transmission_buffer.c \
		file_list_linked_list_manager.c \
		gather_all_file_info.c \
		number_of_files.c \
		send_and_receive_buffer_manager.c \
		serialize_transmission_buffer.c \
		total_of_all_file_sizes.c \
		directory_linked_list_manager.c \
		resolve_file_conflicts.c

source_list = main.c initialize_daemon.c utils.c server.c client.c \
	user_loop_socket_monitor.c \
	file_and_timestamp_linked_list_manager.c  \
	receive_daemon_operation.c daemon_process.c\
	hash.c shasumfile.c receive_handler.c

flags = -Wall -Wextra -pedantic -pedantic-errors

links = -lpthread


handshake_objects_list = $(handshake_list:.c=.o)
objects_list = $(source_list:.c=.o)

alylibc_archive = $(addprefix $(alylibc), $(alylibc_a))
handshakes = $(addprefix $(handshake_directory), $(handshake_list))
sources = $(addprefix $(sources_directory), $(source_list))
objects = $(addprefix $(objects_directory), $(objects_list) $(handshake_objects_list))

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
   install_tool = brew install
   installs = fswatch
else
   install_tool = sudo apt-get install
   installs = inotify
endif


dependencies:

	$(install_tool) $(installs)

all:
	echo $(UNAME_S)
	make all -C libft/
	make all -C $(alylibc)
	gcc -c $(flags) $(sources) $(handshakes)
	gcc -o $(executable) $(objects_list) $(handshake_objects_list) $(alylibc_archive) $(links) libft/libft.a
	mv $(objects_list) $(handshake_objects_list) $(objects_directory)

clean:
	make clean -C $(alylibc)
	rm -f $(objects)

fclean:
	make fclean -C $(alylibc)
	rm -f $(executable)
	rm -f $(objects)

re: fclean all

