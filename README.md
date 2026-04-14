Sistema de Liga de Fútbol en C++

 Descripción del proyecto

Este proyecto consiste en una aplicación de consola desarrollada en **C++** que permite gestionar una liga de fútbol.
El sistema es capaz de leer la configuración desde un archivo externo, registrar resultados de partidos, almacenar la información y generar automáticamente la tabla de posiciones.

El programa mantiene persistencia de datos, lo que significa que la información se conserva aunque se cierre la aplicación.

---

Funcionalidades

* Leer configuración de la liga desde archivo
*  Registrar partidos (equipos, goles, fecha)
*  Guardar partidos en archivo
*  Generar tabla de posiciones automáticamente
*  Ordenar tabla por:

  * Puntos
  * Diferencia de goles
  * Goles a favor
*  Mostrar tabla en consola
*  Menú interactivo

---

 Estructura del proyecto

```
/proyecto
│
├── main.cpp
├── /data
│   ├── config.txt
│   └── partidos.txt
```

---

 Configuración (config.txt)

Ejemplo de archivo:

```
liga=Mi Liga
puntos_victoria=3
puntos_empate=1
puntos_derrota=0
grupo=Equipo1
grupo=Equipo2
grupo=Equipo3
grupo=Equipo4
```

---

Archivo de partidos (partidos.txt)

Formato:

```
fecha,local,visitante,golesLocal,golesVisitante
```

Ejemplo:

```
2026-04-10,Equipo1,Equipo2,2,1
2026-04-11,Equipo3,Equipo4,0,0
```

---

 Cómo ejecutar

1. Compilar el programa:

```
g++ main.cpp -o liga
```

2. Ejecutar:

```
./liga
```

---

 Lógica del programa

1. Se lee la configuración desde `config.txt`
2. Se cargan los partidos desde `partidos.txt`
3. Se construye la tabla de posiciones
4. Se actualizan estadísticas:

   * Partidos jugados
   * Ganados, empatados y perdidos
   * Goles a favor y en contra
   * Diferencia de gol
   * Puntos
5. Se ordena la tabla
6. Se muestra en pantalla

---

 Criterios de clasificación

Los equipos se ordenan según:

1. Mayor cantidad de puntos
2. Mayor diferencia de gol
3. Mayor cantidad de goles a favor

---

Validaciones implementadas

* No permite seleccionar el mismo equipo como local y visitante
* Verifica índices válidos al seleccionar equipos
* Manejo básico de errores al leer archivos

---

 Posibles mejoras

* Guardar tabla en archivo
* Implementar jornadas
* Mostrar estadísticas avanzadas
* Interfaz gráfica
* Validación de datos más robusta

---

 Autor

Proyecto desarrollado por el estudiante Gabriela Campo Ayala como parte de práctica en programación en C++.

---

 Conclusión

Este proyecto demuestra el uso de:

* Estructuras (`struct`)
* Archivos (`ifstream`, `ofstream`)
* Arreglos dinámicos (`vector`)
* Funciones
* Ordenamiento con `sort`

Además, permite aplicar conceptos fundamentales de programación en un caso práctico real.







