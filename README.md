[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=8699321&assignment_repo_type=AssignmentRepo)


# *INFORME FINAL DE PROYECTO AED*

## INTRODUCCIÓN
El siguiente proyecto replica el funcionamiento de la aplicación YAPE a través el algoritmo *Blockchain*. Para ello se desarrollaron las estructuras "Datos", "Bloque" y finalmente "Cadena de bloques" o Blockchain como tal. Al unir éstas estructuras se puede replicar una cadena de bloques con las transacciones monetarias entre usuarios de YAPE guardando los números telefónicos del emisor, receptor y el monto que se transfiere. En ese sentido, a continuación se explicará a detalle la metodología de implementación y los resultados obtenidos al poner el sistema a prueba.

## DESCRIPCIÓN DEL CASO DE ESTUDIO PLANTEADO
En ésta revolución tecnológica, la banca no queda fuera. Es así como se han creado Yape y Plin, aplicaciones que simplifican las transacciones monetarias, haciendo posible el envío de dinero haciendo uso de tan sólo números telefónicos. Se conoce que actualmente Yape hace uso de un algoritmo basado en blockchain para asegurar la confidencialidad de sus transacciones, teniendo como datos: Número de teléfono de emisor, Número de teléfono del receptor y finalmente el monto.

## IMPORTANCIA DEL BLOCKCHAIN EN EL DOMINIO DE DATOS ELEGIDOS
En el año 2019 Facebook intentó crear una especie de monedero virtual basado en blockchain para sus criptomonedas llamadas "Libra". A pesar de que su criptomoneda no tuvo éxito, el sistema que aseguraba la confidencialidad de los datos sí lo hizo. De ésta manera Visa aceptó ser parte de esta revolución tecnológica y adoptó un algoritmo basado en blockchain para permitir la simplificación de éstas operaciones. Gracias a ello el BCP pudo desarrollar su aplicación YAPE, que hasta ahora se mantiene vigente y con muchos usuarios en nuestro país.
La mayor ventaja radica en la facilidad y eficiencia con la que se logra encriptar los datos, tanto en cada bloque como a lo largo de la cadena, logrando que se asemeje a un libro contable codificado. 

## EXPLICACIÓN DE LA ESTRUCTURA DE DATOS DEL BLOCKCHAIN

### BLOCKCHAIN
Tal como lo explica su nombre, es una cadena de bloques interconectados gracias a que cada bloque tiene acceso al código del bloque anterior. De ésta manera, nos podemos asegurar que todos los bloques de la cadena, pertenecen a la cadena. Pues de modificarse el bloque anterior, el bloque actual tendría un código errado y no se podría acceder al bloque.

### BLOCK
En cuanto a la estructura del bloque, éste es un contenedor que almacena los datos necesarios para registrar una transacción monetaria. Cada uno de los datos ingresados modifica el código del bloque, por lo que es fácil darse cuenta si cambió al menos un dígito del número del emisor o receptor o del monto. Finalmente, también almacena el proof of work. 

### PROOF OF WORK
Éste último dato se consigue al obtener cuatro ceros al inicio del código del bloque y para ello se creó un entero "tmp" que es el único dato que podemos modificar libremente dentro del bloque. Ésta variable cambiará dentro de un loop hasta lograr el valor necesario. Para el caso de nuestro proyecto, nos dimos cuenta que lograba ésta condición al pasar los 4 dígitos, por lo que en lugar de aumentar de 1 en 1 se programó para que aumentara de 10 en 10, acortando el tiempo de búsqueda del valor necesario.

## EXPLICACIÓN DE LAS ESTRUCTURAS INTERNAS

Se utilizaron estructuras vistas en el curso dependiendo de sus características. Ya que la estructura que más se parece a una cadena es una lista doblemente enlazada, se utilizó esta para la implementación del blockchain como tal. A continuación se muestra el diagrama de clases de la implementación:

<img width="386" alt="diagrama de clases proyecto aed drawio" src="https://user-images.githubusercontent.com/40670048/205085233-90659e38-4457-4a26-bf40-1c11f3e5c291.png">


### LISTA DOBLEMENTE ENLAZADA
Para representar a la cadena de bloques, se hizo uso de una plantilla de lista doblemente enlazada, pues se asimila mucho a la manera en la que se unen los bloques. Tiene un puntero a la cabeza y otro a la cola. Dentro de la estructura también se hace uso de la estructura nodo, que representaría a cada uno de los bloques que se irán uniendo a la lista.

![image](https://user-images.githubusercontent.com/40670048/196302472-4394cef1-0c67-4635-972c-98b97b1322c8.png)

### BLOCK Y BLOCKCHAIN
Una vez creadas las estructuras del apartado anterior, se pueden crear la estructura *Bloque.h* y *Blockchain.h*. La estrucutura bloque se crea en base a un nodo y contiene los datos necesarios para registrar la transacción. Además, el bloque registra el código del bloque anterior, al cual se puede acceder revisando el *prev* del nodo actual, y también el proof of work que ya se explicó anteriormente. Finalmente, al insertar nuevos bloques, se irá forjando la cadena tal como se muestra en la siguiente imagen:

![image](https://user-images.githubusercontent.com/40670048/196302842-6f1d1241-9164-4322-b071-beee7e1eb522.png)

### AVL
La estructura se eligió porque era sencillo generalizar el tipo de datos que ingresarían, por lo que se pudo guardar un puntero que nos pudiera brindar la información de la transacción. Esto con el fin de evitar duplicar los datos y al mismo tiempo mantenerlos seguros, ya que puede mostrar los datos, mas no modificarlos.

### TRIE
Se crearon dos árboles de éste tipo, uno para los nombres de los usuarios emisores y otro para los receptores. No se utilizó una estructura AVL porque los operadores de comparación ya están sobrecargados con otro atributo. Además, al ser nombres, los trie pueden trabajar con caractares de manera eficiente.

Se crearon dos estructuras con el fin de agilizar la búsqueda por tipo de transacción, ya que los usuarios pueden ser tanto emisores como receptores o ambos casos. En caso se deseara utilizar un solo trie necesitaría un identificador extra a parte del bool "end" para identificar si el nomnbre es de un receptor o de un emisor, la complejidad se mantendría igual, pues se estaría añadiendo sólo un dato más por verificar.

Para poder obtener los datos completos de la transacción, se colocó un puntero al final de cada palabra que dirija a cada uno de los bloques en los que se encuentra el nombre. De ésta manera, nuevamente se evita duplicar datos y se puede obtener la información de manera segura ya que se puede acceder mediante el puntero a la información sólo para ser mostrada, más no editada.

## ANÁLISIS DE LA COMPLEJIDAD BIG O

### MÉTODO INSERTAR
El algoritmo blockchain como tal no tiene una complejidad específica ya que depende de las estructuras con las que se haya creado. Para éste caso en específico, se puede analizar la función *add block* mediante la cual se inserta un nuevo bloque a la cadena. Ésta función accede en O(1) a la lista doblemente enlazada gracias al puntero a la cola y por tanto inserta el nuevo bloque de manera directa. No es necesario recorrer los datos anteriores porque una de las funciones del BlockChain es mantener los datos previos inalterados y seguros, sólo permite ingreso de nuevas transacciones al final de la lista. Por tanto, el método de inserción es O(1).

### MÉTODO BUSCAR
Para éste caso, al igual que en método de inserción, se tomará en cuenta a las estructuras utilizadas para los índices:

* En el caso del AVL, gracias a que esta estructura se autobalancea, mantiene los datos ordenados en su estructura. El atributo que se escogió para lograr este ordenamiento fue el monto de la transacción. De ésta manera, se puede acceder al valor buscado en una complejidad O(logn).

Se sobrecargaron los operadores de comparación para poder realizar las comparaciones con solo el operador monto, lo que significa que si utilizaramos esta estructura para buscar nombres, la complejidad sería O(n).

La complejidad espacial sería O(n x m) ya que depende del tipo de dato que se almacena en el AVL, en este caso un puntero y de la cantidad de datos ingresados en el árbol.

* En el caso del TIRE La complejidad de búsqueda en esta estructura es O(m) tomando en cuenta que m es la longitud de la palabra. Por tanto la complejidad de búsqueda para el caso de los nombres de receptores o emisores sería O(m)

De esta manera, la complejidad de búsqueda para este caso de blockchain es de O(logn) en el caso de que la búsqueda se realice por montos y O(m) en el caso de que la búsqueda se realice por nombres.

La complejidad espacial en éste caso es de O(n + m + l) Siendo n el número de caracteres ingresados, m la cantidad de indicadores de final de palabra y l la cantidad de punteros a los bloques en los que se encuentra el nombre.

#### BÚSQUEDA SIN ÍNDICES
Sin índices es imposible ingresar a verificar los datos internos del bloque, sin embargo, se podría acceder al ID siempre y cuando se tenga un puntero que nos lleve a la información sólo con el fin de verla. En ese sentido, en el caso de que el blockchain no contara con ninguno de los índices utilizados, el método de búsqueda tendría una complejidad de O(n/) pues se tendría que recorrer la lista doblemente enlazada desde la cola y la cabeza hasta dar con el dato o la cantidad de datos que cumplan con la condición de búsqueda. Tomando en cuenta que pueden haber miles de transacciones con 500 soles o miles de personas con el nombre "Juan" la complejidad temporal podría mantenerse, pero sería necesario aumentar la complejidad espacial para poder sacar estos datos de manera ordenada en otra estructura sólo con el fin de mostrarlos. Luego, por razones de seguridad y buen uso de memoria, esta estructura temporal tendría que ser borrada, aumentando, aunque de manera mínima, la complejidad temporal.

## CONCLUSIONES

* El algoritmo blockchain puede ser implementado a partir de estrucutras de datos vistas a lo largo del curso.
* La complejidad espacial y temporal de sus métodos, dependerá de las estrucutras con las que se haya construído el algoritmo. Para este caso en particular, la complejidad de inserción fue O(1) y la de búsqueda O(logn) o O(m) dependiendo del atributo de búsqueda.
* Gracias al uso de índices se puede reducir el tiempo de búsqueda significativamente aunque de ésta manera se esté ocupando más espacio de memoria.
* El proof of work nos permite mantener la confiabilidad y seguridad de los datos guardados en los bloques.

## REFERENCIAS BIBLIOGRÁFICAS
* [“Yape del BCP, la transformación empresarial que retará Libra de Facebook”, por Sergio Sicheri](https://elcomercio.pe/tecnologia/bcp-app-yape-transformacion-empresarial-retara-libra-facebook-sergio-sicheri-nnda-noticia-650359-noticia/?ref=ecr)
* [¿Cómo la Banca puede aprovechar la tecnología Blockchain?](https://www.fisagrp.com/blogs/la-banca-aprovecha-la-tecnologia-blockchain.html)
* [Trie – Estructura de Datos](https://oiaunlam.wordpress.com/2016/05/02/trie/)

