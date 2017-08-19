#!/usr/bin/python

import os, sys

#os: funciones del sistema operativo
#sys: funciones del intérprete de python

if len(sys.argv)!=2:
#sys.argv es una lista de los elementos que se le pasan al script desde la terminal
#len(sys.argv) cuenta cuántos elementos hay en la lista
#Ejemplo: tuterminal7u7$ ./tuscript argumento otroargumento
#aquí hay 3 elementos:      0^       1^         2^    se indexan como los arreglos
# 0: el comando, 1: el primer argumento, 2: el segundo argumento
#en este caso, solo queremos que haya exactamente dos argumentos, incluyendo el comando
    
    print "\nWarning: Only one argument\n"
    quit()

if str(sys.argv[1]).endswith("/"):
#str(sys.argv[1]) es para obtener el string del elemento en el index 1 y ve si termina en "/"
#si se cumple, lo deja así, si no, le añade el "/" en el else de abajo y luego se asigna a una variable
    obj = str(sys.argv[1])
else:
    obj = str(sys.argv[1])+"/"

def lspy(obj):
#definimos la funcioncita y le pasamos la variable con el directorio que guardamos en obj
    countfile = 0
    countdir = 0
    for h in os.listdir(obj):
#os.listdir() es una función que regresa una lista de strings con todos nombres de los archivos de un directorio
#os.listdir(obj) toma lo del directorio de "obj" y "h" en el loop es cada string dentro de esa lista de directorios
        print(h)
        if os.path.isfile(obj+h)==True:
            countfile = countfile+1
        elif os.path.isdir(obj+h)==True:
            countdir = countdir+1
#os.path.isfile() y os.path.isdir() son para verificar que lo que le pasas son directorios o archivos
#ambos tienen "obj+h" porque obj es el string del directorio y h es el string del nombre del archivo, así queda: /directorio/blahblah/archivo
    print "Files: %d \nDirectories: %d" %(countfile,countdir)

quit(lspy(obj))
#fin