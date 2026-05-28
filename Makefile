NAME = ft_malcolm

CC = cc
CFLAGS = -Wall -Wextra -Werror

INCLUDES_DIR = includes
TESTS_DIR = tests

INCLUDES = -I $(INCLUDES_DIR)
TEST_INCLUDES = -I $(INCLUDES_DIR) -I $(TESTS_DIR)

HDRS = $(INCLUDES_DIR)/ft_malcolm.h
TEST_HDRS = $(TESTS_DIR)/test_ft_malcolm.h

SRCS = srcs/main.c \
       srcs/parse_ipv4.c \
       srcs/parse_mac.c \
       srcs/validate_args.c \
       srcs/check_root_privilege.c \
	   srcs/create_arp_socket.c \
	   srcs/get_available_interface.c \
	   srcs/wait_arp_request.c \
	   srcs/send_arp_reply.c \
	   srcs/signal_handler.c


OBJS = $(SRCS:.c=.o)

TEST_NAME = test_ft_malcolm
TEST_SRCS = tests/main.c \
            tests/test_parse_ipv4.c \
            tests/test_parse_mac.c \
            srcs/parse_ipv4.c \
            srcs/parse_mac.c

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

test: $(TEST_NAME)
	./$(TEST_NAME)

$(TEST_NAME): $(TEST_SRCS) $(HDRS) $(TEST_HDRS)
	$(CC) $(CFLAGS) $(TEST_INCLUDES) $(TEST_SRCS) -o $(TEST_NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re test
