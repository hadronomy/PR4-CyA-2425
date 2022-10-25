# CYA-2223
## PRÁCTICA 4

### Descripción
Se pide leer un fichero de código, encontrar una serie de "tokens" 
y escribir los "tokens" en el fichero de salida usando un formato dado.

### Implementación
Hay tres formas principales en las que se puede realizar la práctica.
- Herencia
- Programación funcional
- Metaprogramación

Mi implementación está realizada empleando programación funcional.

Otra opción y seguramente la empleada por la mayoría, es el uso de herencia.
El cual descarté debido a que requeriría redifinir(`override`) una clase principal
por cada uno de los diferentes tokens a encontrar. Además de que al realizarlo de esta forma
se introduce un gran **overhead**, puesto que el compilador tiene que crear una `vtable` por
cada `override` de la clase principal.

Otra opción es herencia mediante `overshadowing` y `static_cast`.
Esto sigue teniendo el problema de que sigue requiriendo la definición
de una clase por cada tipo de token, para su posterior instanciación.

Por esto y por muchas más razones, me decanté por la programación funcional.
El uso de `lambdas` y `std::function` permite que se pueda emplear una única clase
para múltiples tipos de tokens. Y mantiene el `open-closed principle`, evitando la modificación
de la implementación de cualquiera de las clases. A la hora de añadir un token, solo sería necesario
instanciar una nueva definición y añadirla al vector de definiciones que procesa el analizador de código.


Dicha implementación consta principalmente de tres clases.

- TokenDefinition
- Token
- CodeAnalyzer

**TokenDefinition** define todos los datos necesarios para crear, almacenar, manipular 
e imprimir los **Tokens** a partir del texto provisto.

**CodeAnalyzer** se encarga, a partir de una lista de **TokenDefinition**s de encontrar y crear
todos los tokens en el texto dado. Este proceso se realiza línea por línea.

### Compilar
```bash
$ make build
```

### Ejecutar
Desde el directorio principal
```bash
$ ./build/src/cya input_file.cc output_file.txt
```
### Licencia 
[MIT](LICENSE)

