# Minishell
Descripción

El proyecto Minishell es una aplicación en lenguaje C que replica algunas funcionalidades básicas de un shell como bash. Su objetivo principal es familiarizar a los estudiantes con el funcionamiento interno de los shells y los conceptos relacionados con la manipulación de procesos y la gestión de la línea de comandos.

### Funcionalidades Principales

* Interfaz de línea de comandos: Proporciona una interfaz de usuario donde el usuario puede ingresar comandos.
* Ejecución de comandos: Ejecuta comandos simples y algunas expansiones de comandos como echo, cd, env, etc.
* Gestión de procesos: Administra procesos hijos y permite la ejecución en segundo plano.
* Redirección y tuberías: Soporta redirección de entrada/salida y tuberías entre procesos.
* Variables de entorno: Gestiona las variables de entorno del sistema.


# Instalación

Clona el repositorio desde GitHub:

	git clone https://github.com/tu_usuario/minishell.git

Navega al directorio del proyecto:

	cd minishell

Compila el proyecto usando el makefile:

	make

Uso

Ejecuta el programa compilado:

	./minishell

Si los comandos no funcionan prueba a ejecutarlo con permisos de administrador

	sudo ./minishell

Ingresa comandos como lo harías en un shell convencional.