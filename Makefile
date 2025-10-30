# ================== Simple publisher (copy .qmd + sources) ===================
# Usage examples:
#   make NR=1                   # copy theory/ub1/*.qmd(+imgs,+images) and src/ub1/*.{cpp,h,...,txt,dat,png,jpg} → Seafile/ub1
#   make copy_theory NR=2       # only copy theory files for ub2
#   make copy_src NR=3          # only copy source files for ub3
#   make NR=1 SHARE_ROOT=/your/Seafile/path

# -------- parameters you can override on the command line --------
NR          ?= 1
SHARE_ROOT  ?= /home/igor/Seafile/HD-Informatik/WS25-26/num/sol

# -------- derived paths --------
THEORY_DIR  := theory/ub$(NR)
SRC_DIR     := src/ub$(NR)
WEEK_SHARE  := $(SHARE_ROOT)/ub$(NR)

# file extensions to include from src/
SRC_EXTS    := cpp h hpp hh hxx dat png jpg

# -------- default target --------
.PHONY: all
all: publish

# Ensure destination exists
.PHONY: ensure_share_dir
ensure_share_dir:
	@mkdir -p "$(WEEK_SHARE)"

# Copy theory files → Seafile/ub<Nr> (only newer files)
# Includes: *.qmd, *.png, *.jpg and the entire imgs/ folder (if present)
.PHONY: copy_theory
copy_theory: ensure_share_dir
	@if [ -d "$(THEORY_DIR)" ]; then \
	  echo "Copying theory files: $(THEORY_DIR) → $(WEEK_SHARE)"; \
	  rsync -rtu \
	    --include='*/' \
	    --include='*.qmd' \
	    --include='*.png' \
	    --include='*.jpg' \
	    --include='*.dat' \
	    --include='imgs/***' \
	    --exclude='*' \
	    "$(THEORY_DIR)/" "$(WEEK_SHARE)/"; \
	else \
	  echo "Skip: $(THEORY_DIR) not found."; \
	fi

# Copy source files (.cpp/.h/.hpp/.hh/.hxx + assets .txt/.dat/.png/.jpg) → Seafile/ub<Nr> (only newer files)
.PHONY: copy_src
copy_src: ensure_share_dir
	@if [ -d "$(SRC_DIR)" ]; then \
	  echo "Copying source files: $(SRC_DIR) → $(WEEK_SHARE)"; \
	  rsync -rtu --include='*/' \
	    $(foreach ext,$(SRC_EXTS),--include='*.$(ext)') \
	    --exclude='*' \
	    "$(SRC_DIR)/" "$(WEEK_SHARE)/"; \
	else \
	  echo "Skip: $(SRC_DIR) not found."; \
	fi

# One-shot: copy theory + src for this week
.PHONY: publish
publish: copy_theory copy_src
	@echo "Published ub$(NR) → $(WEEK_SHARE)"

# Help
.PHONY: help
help:
	@echo "Make targets:"
	@echo "  make NR=<n>                 # copy theory/ub<n>/*.qmd,*.png,*.jpg(+imgs/) and src/ub<n>/*.{cpp,h,hpp,hh,hxx,txt,dat,png,jpg} to Seafile"
	@echo "  make copy_theory NR=<n>     # only copy theory (.qmd, images, imgs/)"
	@echo "  make copy_src NR=<n>        # only copy source files (+ .txt/.dat/.png/.jpg)"
	@echo "Variables:"
	@echo "  NR=<number>                 # week number (default: 1)"
	@echo "  SHARE_ROOT=<path>           # Seafile base dir (default: $(SHARE_ROOT))"
