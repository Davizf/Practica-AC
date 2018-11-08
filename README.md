Carlos: Subida primera versión de las funciones matemáticas que necesitaremos para la práctica
y también de la clase principal "SpaceObject". Necesitaría revisión por parte del equipo por si
aparece algún error. 

David: Implementado el buble de iteraciones. En cada iteracion incluyen: calculo de las fuerzas de atraccion, las nuevas coordenadas y velocidades para cada asteroide. Falta implementar el rebote entre asteroides, se puede hacer implementando otros dos bucles, pero a lo mejor hay otra forma mas facil. Tambien he implementado el fichero del out.txt que muestran los resultados finales. *Necesitaria revision por parte del equipo para ver que si se ha implementado correctamente los movimientos.

Forma de compilar dos ficheros cpp:
g++ -std=c++14 -Wall -Wextra -Wno-deprecated -Werror -pedantic -pedantic-errors nasteroids-seq.cpp -o math_functionsv1.cpp -o output


Juanjo:Corregido los errores en el fichero de las funciones de matemáticas, importante recordar lo de las fuerzas negativas en el main. Si la fuerza de n2 sobre n1 es positiva la de n1 sobre n2 es negativa. IDEA: en el bucle si estamos en n3 sabemos que para n1 y n2 las fuerzas al calcularla serán negativas.
