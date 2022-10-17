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

### LISTA DOBLEMENTE ENLAZADA
Para representar a la cadena de bloques, se hizo uso de una plantilla de lista doblemente enlazada, pues se asimila mucho a la manera en la que se unen los bloques. Tiene un puntero a la cabeza y otro a la cola. Dentro de la estructura también se hace uso de la estructura nodo, que representaría a cada uno de los bloques que se irán uniendo a la lista.

![image](https://user-images.githubusercontent.com/40670048/196302472-4394cef1-0c67-4635-972c-98b97b1322c8.png)

### BLOCK Y BLOCKCHAIN
Una vez creadas las estructuras del apartado anterior, se pueden crear la estructura *Bloque.h* y *Blockchain.h*. La estrucutura bloque se crea en base a un nodo y contiene los datos necesarios para registrar la transacción. Además, el bloque registra el código del bloque anterior, al cual se puede acceder revisando el *prev* del nodo actual, y también el proof of work que ya se explicó anteriormente. Finalmente, al insertar nuevos bloques, se irá forjando la cadena tal como se muestra en la siguiente imagen:

![image](https://user-images.githubusercontent.com/40670048/196302842-6f1d1241-9164-4322-b071-beee7e1eb522.png)



## ANÁLISIS DE LA COMPLEJIDAD BIG O

### MÉTODO INSERTAR
Debido a que la inserción se realiza de manera manual, es complicado hacer pruebas para registrar el tiempo que toma insertar cierta cantidad de datos, por lo que no se puede realizar una prueba como tal. Sin embargo, se puede analizar la función *add block* mediante la cual se inserta un nuevo bloque a la cadena. Ésta función accede en O(1) a la lista doblemente enlazada gracias al puntero a la cola y por tanto inserta el nuevo bloque de manera directa, sin recorrer los datos previos. Por tanto, el método de inserción es O(1).

### MÉTODO BUSCAR
*Aún no se ha implementado éste método*

## CONCLUSIONES

## REFERENCIAS BIBLIOGRÁFICAS
*[“Yape del BCP, la transformación empresarial que retará Libra de Facebook”, por Sergio Sicheri](https://elcomercio.pe/tecnologia/bcp-app-yape-transformacion-empresarial-retara-libra-facebook-sergio-sicheri-nnda-noticia-650359-noticia/?ref=ecr)
*[¿Cómo la Banca puede aprovechar la tecnología Blockchain?](https://www.fisagrp.com/blogs/la-banca-aprovecha-la-tecnologia-blockchain.html)


