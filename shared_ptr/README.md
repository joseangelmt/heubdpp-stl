# unique_ptr

En este directorio tienes el código del vídeo [Crea tu propio shared_ptr](https://youtu.be/E-kyWujQI0U) en el que aprenderemos a usar el tipo _std::shared\_ptr_ y en el que programaremos nuestra propia implementación.

Este tipo al igual que _std::unique\_ptr_ va a permitir que nos olvidemos de las fugas de memoria si se nos olvida hacer un _delete_, se encargará de cerrar recursos por nosotros y además simplificará el código pues no tendremos que llenarlo de _delete_ o de llamadas a funciones o métodos que se encarguen de liberar recursos, pero éste sí que nos va a permitir realizar copias del puntero inteligente.
