default: all

DAYS := $(shell seq 1 9)
BINS := $(addprefix day, $(DAYS))
RUNS := $(addprefix run, $(BINS))

.PHONY: all clean $(RUNS)

all: $(RUNS)

# Static Pattern Rule for compiling: [targets] : [target-pattern] : [prereq]
$(BINS): day%: day%.c
	$(CC) -o $@ $<

# Static Pattern Rule for running: [targets] : [target-pattern] : [prereq]
$(RUNS): runday%: day%
	time ./$<

clean:
	rm -f $(BINS)

# Add this to ~/.zshrc to make autocomplete in shell work
# zstyle ':completion:*:make:*:targets' call-command true
