build :
	gcc Progc/prog_t.c -o Progc/prog_t
	gcc Progc/prog_s.c -o Progc/prog_s
run_t : 
	./script_principal.sh t
run_d1 :
	./script_principal.sh d1
run_d2 :
	./script_principal.sh d2	
run_l :
	./script_principal.sh l
run_s :
	./script_principal.sh s
clean :
	rm Progc/prog_t 
	rm Progc/prog_s
help : 
	./script_principal.sh h
	
