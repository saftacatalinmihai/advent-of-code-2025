default: all

# Find all files matching the pattern
SRCS := $(wildcard day*.c)

# Derive binary and run names from found sources
BINS := $(SRCS:.c=)
RUNS := $(addprefix run, $(BINS))

.PHONY: all clean $(RUNS)

all: $(RUNS)

# Static Pattern Rule for compiling: [targets] : [target-pattern] : [prereq]
$(BINS): day%: day%.c
	$(CC) -O3 -o $@ $<

# Static Pattern Rule for running: [targets] : [target-pattern] : [prereq]
$(RUNS): runday%: day%
	time ./$<

clean:
	rm -f $(BINS)

# Add this to ~/.zshrc to make autocomplete in shell work
# zstyle ':completion:*:make:*:targets' call-command true
