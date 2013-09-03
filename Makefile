#
# This file is here for testing purposes. It builds all the example projects.  
# This is used for testing mostly
#

projects=$(shell find . -iname ".config"|while read line; do dirname $$line; done)

define project_template
compile/$(1):
	cd $(1) && make && make silentoldconfig && make build

clean/$(1):
	-cd $(1) && make mrproper

all-compile+=compile/$(1)
all-clean+=clean/$(1)
endef 

$(foreach p,$(projects),$(eval $(call project_template,$(p))))

all:
	@echo "Woot, normally you don't need to run it."

compile: $(all-compile) 
	@echo "All projects compiled fine. Take a break!"

clean: $(all-clean)
	@echo "mrproperred all projects"

.PHONY+=$(all-compile) $(all-clean) 