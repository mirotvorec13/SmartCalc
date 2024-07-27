# Настройки для компиляции проекта
CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -Werror
LIB_DIR=backend
BUILD_DIR=${LIB_DIR}/build
INSTALL_DIR = SmartCalc
NAME_PROJECT = frontend
LIB=s21_calc.a

CFILES=$(shell find ${LIB_DIR}/lib -name '*.c')
HFILES=$(shell find ${LIB_DIR}/lib -name '*.h')
OBJECTS=$(CFILES:%.c=$(BUILD_DIR)/%.o)

# Настройки для компиляции тестов
TEST_NAME=s21_tests
TEST_CFILES=$(shell find ${LIB_DIR}/tests -name '*.c')
TEST_HFILES=$(shell find ${LIB_DIR}/tests -name '*.h')

# Определение библиотек для тестов
ifeq ($(shell command -v pkg-config 2> /dev/null),)
	UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
		LIBSUBUNIT := $(shell ldconfig -p 2> /dev/null | grep libsubunit.so)
		ifeq ($(LIBSUBUNIT),)
			TEST_FLAGS = -lcheck -lm
		else
			TEST_FLAGS = -lcheck -lsubunit -lm
		endif
    endif
    ifeq ($(UNAME_S),Darwin)
        TEST_FLAGS = -lpthread -lcheck -lm
    endif
else
    TEST_FLAGS = $(shell pkg-config --cflags --libs check) -lm
endif

# Настройки для gcovr
GCOVR := $(shell command -v gcovr 2> /dev/null)
ifeq ($(GCOVR),)
    GCOVR := ~/.local/bin/gcovr
endif
GCOV_FLAG=--coverage -lgcov
GCOV_REPORT=${LIB_DIR}/gcov_report/gcov_report.html

# Настройки для отладки
DEBUG_FLAG=-g
DEBUG_DIR=${LIB_DIR}/debug
DEBUG_NAME=debug.out

.PHONY: all test gcov_report clean 
.PHONY: rebuild gcov val check debug clean_gcovr clean_all style test_build

all: rebuild

rebuild: clean $(LIB) build

$(LIB): $(OBJECTS)
	@ar rc ${LIB_DIR}/$(LIB) $(OBJECTS)
	@ranlib ${LIB_DIR}/$(LIB)
	@echo;echo "Library compiled: ${LIB_DIR}/$(LIB)";echo;

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c -o $@ $<
	
build: $(LIB)
	qmake6 -makefile -o $(NAME_PROJECT)/Makefile $(NAME_PROJECT)/ || qmake -makefile -o $(NAME_PROJECT)/Makefile $(NAME_PROJECT)/
	$(MAKE) -C $(NAME_PROJECT)

install: build
	@mkdir -p $(INSTALL_DIR)
	@cp $(NAME_PROJECT)/$(INSTALL_DIR)/* $(INSTALL_DIR)/
	@echo;echo "SmartCalc installed"

uninstall:
	@rm -rf $(INSTALL_DIR)
	@echo;echo "SmartCalc uninstalled"

dvi: help/readme.texi
	texi2dvi --dvipdf help/readme.texi

dist: install
	tar -zcf SmartCalc.tar.gz SmartCalc

run: install
	./$(INSTALL_DIR)/SmartCalc

test_build: clean_all $(LIB)
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(TEST_CFILES) ${LIB_DIR}/$(LIB) -o $(BUILD_DIR)/$(TEST_NAME) $(TEST_FLAGS)
test: test_build
	@$(BUILD_DIR)/$(TEST_NAME)

gcov_report:
	@$(MAKE) test CFLAGS="$(CFLAGS) $(GCOV_FLAG)" >/dev/null
	@mkdir -p ${LIB_DIR}/gcov_report
	@rm -r $(BUILD_DIR)/*_t*.gc?? || true
	@$(GCOVR) --html-details $(GCOV_REPORT) 2>/dev/null || true
	# @$(GCOVR) --xml build/cov.xml 2>/dev/null || true
	@ln -s $(GCOV_REPORT) ./gcov_report.html || true
	@$(MAKE) clean_gcovr >/dev/null

	@if [ ! -f $(GCOV_REPORT) ]; then echo;echo "Ошибка. Проверте доступность gcovr.";echo; fi
	@if [ -f $(GCOV_REPORT) ]; then echo;echo "Отчет сгенерирован в gcov_report.html";echo; fi

gcov: gcov_report
	@if [ -f $(GCOV_REPORT) ]; then xdg-open $(GCOV_REPORT); fi

val: test_build
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes $(BUILD_DIR)/$(TEST_NAME)
	@$(MAKE) clean_all >/dev/null

check: val
	cppcheck --enable=all --suppress=missingIncludeSystem backend/
	find . -name '*.[ch]' | xargs clang-format -n --style='file:../materials/linters/.clang-format'
	@echo;

style:
	find . -name '*.[ch]' | xargs clang-format -i --style='file:../materials/linters/.clang-format'
# rm .clang-format

debug: clean_all
	@$(MAKE) $(LIB) CFLAGS="$(DEBUG_FLAG)" >/dev/null 
	@$(CC) $(DEBUG_FLAG) $(DEBUG_DIR)/*.c -L${LIB_DIR} -l:$(LIB) -o $(DEBUG_DIR)/$(DEBUG_NAME) -lm
	@echo;$(DEBUG_DIR)/$(DEBUG_NAME);echo;

clean_gcovr:
	@rm -f *.gcda *.gcno $(BUILD_DIR)/*.gcda $(BUILD_DIR)/*.gcno $(BUILD_DIR)/$(TEST_NAME)

clean_all: clean_gcovr
	@rm -f ${LIB_DIR}/$(OBJECTS)
	@rm -f ${LIB_DIR}/$(LIB) 
	@rm -f ${LIB_DIR}/$(TEST_NAME) $(DEBUG_DIR)/$(DEBUG_NAME)
	@rm -rf ${LIB_DIR}/gcov_report *.html
	@rm -rf $(BUILD_DIR)
	@rm -rf SmartCalc
	@rm -f $(NAME_PROJECT)/moc_*.cpp
	@rm -f $(NAME_PROJECT)/moc_*.h
	@rm -f $(NAME_PROJECT)/Makefile
	@rm -f $(NAME_PROJECT)/*.o
	@rm -f $(NAME_PROJECT)/.qmake.stash
	@rm -rf $(NAME_PROJECT)/SmartCalc
	@rm -f *.dvi *.log *.pdf *.tar.gz

clean: clean_all
	@echo;echo "Clean complete";echo;
