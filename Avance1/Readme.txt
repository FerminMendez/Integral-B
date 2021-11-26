Integral B

SICT0302B: Toma decisiones

En el juego de mesa King of Tokyo, las power cards son piezas clave para ganar.
Pero los recursos son limitados y tenemos que elegir sabiamente.
Por eso en un archivo de texto escribí la lista de adyacencia del grafo que representa la sinergía que existe entre dos cartas
Si, es decir, si la carta hace buena sinergía con la carta B ambas estan conectadas.
Además si A se conecta con B, B con C pero A no está con C, entonces decimos que tienen un sinergía debil.

En este programa, dadas las cartas del jugador y las cartas disponibles a la venta señala las cartas tienen al menos una sinergía debil para que se considere para la compra.

Algoritmo de busqueda:
Para este caso usamos BFS hasta dos niveles. Dado que en el queue se reutiliza la misma cola para agregar niveles y no hay separación
opté por hacer dos queue dado que solo son dos niveles. Aunque para la generalización es conveniente añadir un parametro de profundidad u otro método.

Descripción del programa:

-El programa lee el grafo de sinergias.
-Crea un mercado de 3 cartas
-Asigna algunas cartas al usuario
-Recomienda que cartas hacen sinergia en los dos niveles más cercanos en el grafo.