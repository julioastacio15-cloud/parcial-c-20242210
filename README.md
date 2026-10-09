\# Parcial de algoritmos en C



\- Estudiante: Julio Peguero

\- Matrícula: 20242210

\- Reto: Inventario: caídas críticas de existencias



\## Descripción



El programa analiza una matriz de inventario e identifica caídas críticas entre columnas consecutivas de una misma fila. Calcula la cantidad de eventos, sus impactos, las rachas y la prioridad de revisión.



\## Archivos del proyecto



\- `20242210.c`: código fuente del programa.

\- `ANALISIS.md`: análisis del problema, pseudocódigo, prueba de escritorio y casos propios.

\- `evidencias/pruebas-17-casos.png`: captura de la comparación de los 17 casos.



\## Compilar en Windows



Abre PowerShell en la carpeta principal del proyecto y ejecuta:



```powershell

gcc -std=c11 -Wall -Wextra .\\20242210.c -o .\\output\\20242210.exe

