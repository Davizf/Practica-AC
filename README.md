<b>Problemas actuales</b><br/>
Carlos: Falta mejorar la precisión de la versión paralela. (Vigilar velocidades)

David: 
- Resultados diferentes entre nasteroids-seq y nasteroids-seqcopia, nasteroids-seq parece tener resultados mas precisos<br/>
- Compilando nasteroids-seq y ejecutar ./a.out 100 100 100 100 solo imprime una vez "Borde", no imprime "Funcion de choque invocada". Entonces nuestra impresicion para los input 100 100 100 100 no tiene que ver con Choques. <br/>

Juanjo: Ya sale muy parecido al profe pero en algunos casos , salen cosas con cas una unidad de variación

<b>Forma de compilar dos ficheros cpp:</b> <br/>
g++ -std=c++14 -Wall -Wextra -Wno-deprecated -Werror -pedantic -pedantic-errors nasteroids-seq.cpp -o math_functionsv1.cpp -o output

