CURRENT_DIR := $(CURDIR)
build :
	
	gcc prog_t.c -o prog_t
	gcc prog_s.c -o prog_s
droit :
	
	chmod 777 prog_d1.sh
	chmod 777 prog_d2.sh
	chmod 777 prog_l.sh
	chmod 777 prog_t.sh
	chmod 777 prog_s.sh
	cd $(CURRENT_DIR)/.. && chmod 777 script_principal.sh
t: 
	
	cd $(CURRENT_DIR)/.. && ./script_principal.sh t
d1 :
	
	cd $(CURRENT_DIR)/.. && ./script_principal.sh d1
d2 :
	
	cd $(CURRENT_DIR)/.. && ./script_principal.sh d2	
l :
	
	cd $(CURRENT_DIR)/.. && ./script_principal.sh l
s :
	
	cd $(CURRENT_DIR)/.. && ./script_principal.sh s
clean :
	
	rm prog_t 
	rm prog_s
help : 
	cd $(CURRENT_DIR)/.. && ./script_principal.sh h
	
