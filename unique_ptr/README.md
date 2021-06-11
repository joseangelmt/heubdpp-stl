# unique_ptr

En este directorio tienes el código del vídeo [Crea tu propio unique_ptr](https://youtu.be/-fygalS1ZVg) en el que aprenderemos una de las utilidades más importantes de la librería STL: el tipo _unique\_ptr_. 

En un segundo vídeo [Especializando unique_ptr para arrays](https://youtu.be/fzAG9GB3WCo) aprendemos cómo especializar nuestra clase unique_ptr para hacer que sea compatible con arrays de objetos.

Este tipo va a permitir que nos olvidemos de las fugas de memoria si se nos olvida hacer un _delete_, se encargará de cerrar recursos por nosotros y además simplificará el código pues no tendremos que llenarlo de _delete_ o de llamadas a funciones o métodos que se encarguen de liberar recursos.
