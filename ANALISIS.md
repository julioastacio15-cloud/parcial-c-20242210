\# Análisis del problema



\## Objetivo



Analizar una matriz de inventario donde cada fila representa una entidad y cada columna representa un día. El programa identifica las caídas críticas, calcula su impacto y resume los eventos por fila y por columna para determinar la fila prioritaria y la columna destacada.



\## Entradas



\- `N`: cantidad de filas de la matriz.

\- `M`: cantidad de columnas de la matriz.

\- `L`: límite inferior.

\- `U`: límite superior.

\- `inventario\[N]\[M]`: unidades disponibles por entidad y día.



Los datos se leen como enteros separados por espacios o saltos de línea.



\## Restricciones y validación



\- `1 <= N <= 30`

\- `1 <= M <= 30`

\- `0 <= L <= U <= 1000`

\- Cada valor de inventario debe estar entre `0` y `1000`, inclusive.

\- Las dimensiones se validan antes de leer la matriz.

\- Si alguna restricción falla, el programa imprime únicamente `ERROR` y termina.



\## Regla para identificar eventos



La primera columna no puede generar un evento porque no tiene una columna anterior. Para cada posición desde la segunda columna, se compara el valor actual con el valor anterior de la misma fila:



\- `p`: valor de la columna anterior.

\- `x`: valor de la columna actual.



La posición es un evento cuando:



```text

j >= 1 Y p > U Y x <= L

```



El impacto del evento es `p - x`. Si la posición no es un evento, su impacto es `0`. Los valores originales de la matriz no se modifican.



\## Resultados



Para cada fila se calcula:



\- La cantidad de eventos.

\- La suma de sus impactos.

\- La longitud de la mayor racha de eventos en columnas consecutivas.

\- La columna donde inicia esa racha, usando índices desde `1`.

\- Si hay varias rachas máximas, se conserva la que comienza primero.

\- Si la fila no tiene eventos, la racha máxima y su inicio son `0`.



También se calcula un vector con la cantidad de eventos de cada columna, sumando los eventos de todas las filas.



La fila prioritaria se determina usando estos criterios, en este orden:



1\. Mayor longitud de racha.

2\. Mayor impacto total.

3\. Mayor cantidad de eventos.

4\. Menor número de fila.



La columna destacada es la que tiene más eventos. Si varias columnas empatan, se elige la de menor número. Si no hay eventos en toda la matriz, la prioridad y la columna destacada son `0`.



\## Salidas



El programa imprime, en este orden:



1\. Una línea por fila con sus eventos, impacto, racha e inicio.

2\. El vector de conteos por columna.

3\. La fila prioritaria.

4\. La columna destacada.



Los índices de filas, columnas e inicios se muestran comenzando en `1`. La salida usa las etiquetas exactas del enunciado y no incluye mensajes adicionales.



\## Variables y arreglos principales



\- `inventario\[30]\[30]`: almacena la matriz original.

\- `eventos\_columna\[30]`: acumula los eventos de cada columna.

\- `cantidad\_eventos`: cuenta eventos en la fila actual.

\- `impacto\_total`: suma los impactos de la fila actual.

\- `racha\_actual`: cuenta los eventos consecutivos que se están recorriendo.

\- `inicio\_actual`: guarda la columna inicial de la racha actual.

\- `racha\_maxima`: guarda la mayor racha encontrada en la fila.

\- `inicio\_racha\_maxima`: guarda dónde empieza la mayor racha.

\- `fila\_prioritaria`: guarda la fila que ocupa el primer lugar según los desempates.

\- `total\_eventos`: permite detectar si hubo al menos un evento en la matriz.



\# Pseudocódigo



```text

INICIO



&#x20;   Leer N, M, L, U



&#x20;   Si no se pudieron leer los cuatro datos

&#x20;      O N < 1 O N > 30

&#x20;      O M < 1 O M > 30

&#x20;      O L < 0 O U > 1000

&#x20;      O L > U Entonces

&#x20;       Imprimir "ERROR"

&#x20;       Terminar

&#x20;   FinSi



&#x20;   Para cada fila i desde 0 hasta N - 1

&#x20;       Para cada columna j desde 0 hasta M - 1

&#x20;           Leer inventario\[i]\[j]



&#x20;           Si el valor no se pudo leer

&#x20;              O inventario\[i]\[j] < 0

&#x20;              O inventario\[i]\[j] > 1000 Entonces

&#x20;               Imprimir "ERROR"

&#x20;               Terminar

&#x20;           FinSi

&#x20;       FinPara

&#x20;   FinPara



&#x20;   Inicializar cada posición de eventos\_columna en 0

&#x20;   Inicializar total\_eventos en 0

&#x20;   Inicializar fila\_prioritaria en 0



&#x20;   Para cada fila i desde 0 hasta N - 1



&#x20;       cantidad\_eventos <- 0

&#x20;       impacto\_total <- 0

&#x20;       racha\_actual <- 0

&#x20;       racha\_maxima <- 0

&#x20;       inicio\_actual <- 0

&#x20;       inicio\_racha\_maxima <- 0



&#x20;       Para cada columna j desde 0 hasta M - 1



&#x20;           evento <- FALSO

&#x20;           impacto <- 0



&#x20;           Si j >= 1 Y inventario\[i]\[j - 1] > U

&#x20;                        Y inventario\[i]\[j] <= L Entonces

&#x20;               evento <- VERDADERO

&#x20;               impacto <- inventario\[i]\[j - 1] - inventario\[i]\[j]

&#x20;           FinSi



&#x20;           Si evento Entonces

&#x20;               cantidad\_eventos <- cantidad\_eventos + 1

&#x20;               impacto\_total <- impacto\_total + impacto

&#x20;               eventos\_columna\[j] <- eventos\_columna\[j] + 1

&#x20;               total\_eventos <- total\_eventos + 1



&#x20;               Si racha\_actual = 0 Entonces

&#x20;                   inicio\_actual <- j + 1

&#x20;               FinSi



&#x20;               racha\_actual <- racha\_actual + 1



&#x20;               Si racha\_actual > racha\_maxima Entonces

&#x20;                   racha\_maxima <- racha\_actual

&#x20;                   inicio\_racha\_maxima <- inicio\_actual

&#x20;               FinSi

&#x20;           SiNo

&#x20;               racha\_actual <- 0

&#x20;           FinSi



&#x20;       FinPara



&#x20;       Si cantidad\_eventos = 0 Entonces

&#x20;           racha\_maxima <- 0

&#x20;           inicio\_racha\_maxima <- 0

&#x20;       FinSi



&#x20;       Imprimir datos de la fila i + 1:

&#x20;           "FILA", i + 1,

&#x20;           "EVENTOS", cantidad\_eventos,

&#x20;           "IMPACTO", impacto\_total,

&#x20;           "RACHA", racha\_maxima,

&#x20;           "INICIO", inicio\_racha\_maxima



&#x20;       Si cantidad\_eventos > 0 Entonces

&#x20;           Si fila\_prioritaria = 0

&#x20;              O racha\_maxima > mayor\_racha

&#x20;              O (racha\_maxima = mayor\_racha

&#x20;                 Y impacto\_total > mayor\_impacto)

&#x20;              O (racha\_maxima = mayor\_racha

&#x20;                 Y impacto\_total = mayor\_impacto

&#x20;                 Y cantidad\_eventos > mayor\_cantidad) Entonces



&#x20;               fila\_prioritaria <- i + 1

&#x20;               mayor\_racha <- racha\_maxima

&#x20;               mayor\_impacto <- impacto\_total

&#x20;               mayor\_cantidad <- cantidad\_eventos

&#x20;           FinSi

&#x20;       FinSi



&#x20;   FinPara



&#x20;   Imprimir "COLUMNAS" seguido de eventos\_columna\[0] hasta eventos\_columna\[M - 1]



&#x20;   Si total\_eventos = 0 Entonces

&#x20;       Imprimir "PRIORIDAD 0"

&#x20;       Imprimir "COLUMNA 0"

&#x20;   SiNo

&#x20;       columna\_destacada <- 0



&#x20;       Para cada columna j desde 1 hasta M - 1

&#x20;           Si eventos\_columna\[j] > eventos\_columna\[columna\_destacada] Entonces

&#x20;               columna\_destacada <- j

&#x20;           FinSi

&#x20;       FinPara



&#x20;       Imprimir "PRIORIDAD", fila\_prioritaria

&#x20;       Imprimir "COLUMNA", columna\_destacada + 1

&#x20;   FinSi



FIN

```



Al recorrer las filas en orden ascendente y reemplazar la prioridad solo cuando mejora alguno de los tres primeros criterios, los empates completos conservan la fila menor. De manera similar, al actualizar la columna destacada solo cuando el conteo es estrictamente mayor, los empates conservan la columna menor.

# Prueba de escritorio

Se usan los límites `L = 5` y `U = 15`, con esta fila de inventario:

```text
20 5 22 4 30 5 15
```

Para cada columna desde la segunda, se compara el valor actual (`x`) con el anterior (`p`). Hay evento si `p > 15` y `x <= 5`. El impacto es `p - x` cuando hay evento; en los demás casos es `0`.

| Columna | Valor actual (x) | Valor anterior (p) | ¿Es evento? | Impacto | Racha actual |
|---:|---:|---:|:---:|---:|---:|
| 1 | 20 | — | No, es la primera columna | 0 | 0 |
| 2 | 5 | 20 | Sí: 20 > 15 y 5 <= 5 | 15 | 1 |
| 3 | 22 | 5 | No: 5 no es mayor que 15 | 0 | 0 |
| 4 | 4 | 22 | Sí: 22 > 15 y 4 <= 5 | 18 | 1 |
| 5 | 30 | 4 | No: 4 no es mayor que 15 | 0 | 0 |
| 6 | 5 | 30 | Sí: 30 > 15 y 5 <= 5 | 25 | 1 |
| 7 | 15 | 5 | No: 5 no es mayor que 15 | 0 | 0 |

**Resumen de la fila:** hay 3 eventos y el impacto total es `15 + 18 + 25 = 58`. La racha máxima es 1 y empieza en la columna 2. Aunque hay tres eventos, están separados por columnas sin evento.

La racha máxima no puede superar 1 con esta regla: después de un evento, el valor actual es `x <= L`; como `L <= U`, ese valor no puede ser mayor que `U` para iniciar otro evento en la columna siguiente.

## Entrada de la prueba de escritorio

```text
1 7 5 15
20 5 22 4 30 5 15
```

## Salida esperada

```text
FILA 1 EVENTOS 3 IMPACTO 58 RACHA 1 INICIO 2
COLUMNAS 0 1 0 1 0 1 0
PRIORIDAD 1
COLUMNA 2
```

# Casos de prueba propios

## Caso propio 1: desempate de prioridad

**Entrada:**

```text
3 6 5 15
20 5 20 5 20 5
50 5 0 0 0 0
20 5 20 5 20 5
```

**Salida esperada:**

```text
FILA 1 EVENTOS 3 IMPACTO 45 RACHA 1 INICIO 2
FILA 2 EVENTOS 1 IMPACTO 45 RACHA 1 INICIO 2
FILA 3 EVENTOS 3 IMPACTO 45 RACHA 1 INICIO 2
COLUMNAS 0 3 0 2 0 2
PRIORIDAD 1
COLUMNA 2
```

**Justificación:** las tres filas tienen racha máxima 1 e impacto total 45. La fila 1 tiene más eventos que la fila 2. Las filas 1 y 3 empatan también en cantidad de eventos, por lo que se elige la fila 1, que tiene el número menor. La columna 2 tiene más eventos que las demás columnas y es la columna destacada.

## Caso propio 2: valores iguales a los límites

**Entrada:**

```text
2 5 5 15
15 5 16 6 20
20 5 15 5 16
```

**Salida esperada:**

```text
FILA 1 EVENTOS 0 IMPACTO 0 RACHA 0 INICIO 0
FILA 2 EVENTOS 1 IMPACTO 15 RACHA 1 INICIO 2
COLUMNAS 0 1 0 0 0
PRIORIDAD 2
COLUMNA 2
```

**Justificación:** en la fila 1, la caída de 15 a 5 no es evento porque el valor anterior debe ser estrictamente mayor que `U`; 15 es igual a `U`. En la fila 2, la caída de 20 a 5 sí es evento. La caída posterior de 15 a 5 no lo es porque el valor anterior tampoco es estrictamente mayor que `U`. Este caso comprueba los límites inclusivos y estrictos de la condición.

