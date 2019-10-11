# RECEBER
nc -p 5000 -l > mac422shell.c   
# ENVIAR
nc 172.19.50.2 5000 < mac422shell.c 
