<b>Problemas actuales</b><br/>
Carlos: Resultados precisos comparando con la versión secuencial. La versión paralela ya es más rápida que la secuencial, pero estamos seguros de que se podría optimizar todavía más.

David: <br/> <br/>
Juanjo: Ya sale muy parecido al profe pero en algunos casos , salen cosas con cas una unidad de variación

<b>Forma de compilar dos ficheros cpp:</b> <br/>
g++ -std=c++14 -Wall -Wextra -Wno-deprecated -Werror -pedantic -pedantic-errors -O3 -DNDEBUG  nasteroids-seq.cpp  -o math_functions.cpp -o output
<br/>
g++ -std=c++14 -Wall -Wextra -Wno-deprecated -Werror -pedantic -pedantic-errors -O3 -DNDEBUG -fopenmp  nasteroids-par.cpp  -o math_functions.cpp -o output

