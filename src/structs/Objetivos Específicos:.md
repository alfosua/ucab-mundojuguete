Objetivos Específicos:

[x] 1. Gestionar el historial de entradas/salidas de inventario: Utilizar una pila para registrar
las últimas transacciones de entrada y salida de cada juguete, permitiendo rastrear los
movimientos recientes del inventario.

[ ] 2. Administrar los pedidos pendientes: Emplear una cola para gestionar los pedidos de juguetes que aún no han sido procesados o enviados.
    - Falta el proceso de Procesamiento

[x] 3. Organizar el inventario por código de producto: Implementar un árbol binario de búsqueda para indexar y buscar eficientemente los juguetes por su código único de producto. Esto facilitará la búsqueda, actualización y eliminación de artículos.

[ ] 4. Representar las relaciones entre juguetes: Utilizar un grafo para modelar posibles relaciones entre juguetes, como "se compra frecuentemente junto con", "es una variante de", o "requiere ensamblaje con". Esto podría utilizarse para sugerencias de compra o para gestionar componentes.

Funcionalidades Requeridas:

[x] 1. Registro de Juguetes: Permitir el registro de nuevos juguetes en el inventario, incluyendo
atributos como código de producto (único), nombre, descripción, cantidad en stock,
precio de venta y categoría.

[x] 2. Entrada de Inventario: Permitir registrar la entrada de nuevas unidades de un juguete al
inventario. Cada entrada deberá registrarse en la pila de historial del juguete.

[x] 3. Salida de Inventario (Venta): Permitir registrar la venta de unidades de un juguete,
disminuyendo la cantidad en stock. Cada venta deberá registrarse en la pila de historial
del juguete.

[x] 4. Consulta de Inventario: Permitir consultar la información detallada de un juguete
específico buscando por su código de producto utilizando el árbol binario de búsqueda.

[ ] 5. Gestión de Pedidos:
    [x] Creación de Pedidos: Permitir crear nuevos pedidos de juguetes. Estos pedidos se añadirán a la cola de pedidos pendientes.
    [ ] Procesamiento de Pedidos: Permitir marcar pedidos como procesados, removiéndolos de la cola.
    [x] Visualización de Pedidos Pendientes: Mostrar la lista de pedidos pendientes en el orden en que fueron recibidos.

[x] 6. Historial de Movimientos: Permitir visualizar el historial reciente de entradas y salidas de un juguete específico, utilizando la pila asociada a ese juguete.

[ ] 7. Búsqueda por Categoría (Utilizando el Árbol): Permitir listar los juguetes pertenecientes a una categoría específica.

[ ] 8. Sugerencias/Relaciones: Se implementa el grafo para permitir mostrar juguetes relacionados a un juguete específico.
