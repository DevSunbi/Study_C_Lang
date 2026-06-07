.RECIPEPREFIX := >

# =========================
# Common config
# =========================

CC := aarch64-linux-gnu-gcc
SYSROOT := $(HOME)/rpi-sysroot

PI_USER := sunbi
PI_HOST := 100.66.20.91
PI_DIR := ~

ARG ?= On

# =========================
# Build flags
# =========================

CPPFLAGS := \
  --sysroot=$(SYSROOT) \
  -I$(SYSROOT)/usr/include \
  -I$(SYSROOT)/usr/local/include

CFLAGS := \
  -Wall \
  -Wextra \
  -O2 \
  -pthread

LDFLAGS := \
  --sysroot=$(SYSROOT) \
  -L$(SYSROOT)/lib/aarch64-linux-gnu \
  -L$(SYSROOT)/usr/lib/aarch64-linux-gnu \
  -L$(SYSROOT)/usr/lib \
  -L$(SYSROOT)/usr/local/lib \
  -Wl,-rpath-link=$(SYSROOT)/lib/aarch64-linux-gnu \
  -Wl,-rpath-link=$(SYSROOT)/usr/lib/aarch64-linux-gnu \
  -Wl,-rpath-link=$(SYSROOT)/usr/lib \
  -Wl,-rpath-link=$(SYSROOT)/usr/local/lib

LDLIBS := \
  -lwiringPi \
  -pthread

# =========================
# Pattern build rule
# =========================

%: %.c
>$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ $(LDFLAGS) $(LDLIBS)

# =========================
# Utility targets
# =========================

.PHONY: clean

check-%: %
>file $*
>readelf -l $* | grep interpreter || true

send-%: %
>scp $* $(PI_USER)@$(PI_HOST):$(PI_DIR)/

run-%: %
>scp $* $(PI_USER)@$(PI_HOST):$(PI_DIR)/
>ssh $(PI_USER)@$(PI_HOST) 'cd $(PI_DIR) && ./$* $(ARG)'

run-sudo-%: %
>scp $* $(PI_USER)@$(PI_HOST):$(PI_DIR)/
>ssh $(PI_USER)@$(PI_HOST) 'cd $(PI_DIR) && sudo ./$* $(ARG)'

trace-%: %.c
>$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $* $(LDFLAGS) $(LDLIBS) -Wl,-t

clean:
>rm -f blink led hello test main
