#define CLEAR "clear" //Depende si se compila en windows

#include <stdio.h>	
#include <string.h>
#include <stdlib.h>
#include <locale.h> 
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
 
#define CaracteresMaximos 80
#define valorCent -1

using namespace std;
 
// Título, Apellido del autor, Nombre del autor, Costo de venta (en quetzales), Editorial, Tipo de libro (científico, literatura, recreativo, juvenil, etc.), Fecha de copyright, Número de ejemplares disponibles, Estado (1 para libros que pueden solicitarse a la editorial y 0 para libros agotados en la editorial y que no se reimprimen).

/* Estructuras */
struct libro {
	int codigo;
	char titulo[CaracteresMaximos]; 
	char apellidoAutor[CaracteresMaximos]; 
	char nombreAutor[CaracteresMaximos]; 
	double costo; 
	char editorial[CaracteresMaximos]; 
  char tipo[CaracteresMaximos];
  char fecha[CaracteresMaximos]; 
	int cantidad;
  char estado[CaracteresMaximos];


};

struct compra {
	char nombreCliente[CaracteresMaximos]; 
	char direccion[CaracteresMaximos];
	double edad; 
	int codigo;
	char titulo[CaracteresMaximos];
  double costo;
  double impuesto;
	int cantidad;
};

 
typedef struct libro Libro;
typedef struct compra Compra;

/* Opciones del Menú */
void menuPrincipal();
void menuInsertar();
void menuBuscar();
void menuEliminar();
void menuMostrar();
void menuModificar();
void menuEliminarFisica();
void Login();


 
/* Funciones para manejar el archivo directamente */
Libro *obtenerLibros(int *n); /* Obtiene un vector dinámico de libros */
char existeLibro(int codigoLibro, Libro *libro); /* Busca si existe el libro en el archivo de libros */
char insertarLibro(Libro libro); /* Inserta el libro al final del archivo */
char eliminarLibro(int codigoLibro); /* Eliminar el libro de código codigo del archivo */
char eliminacionFisica(); /* Realiza la eliminación física de registros inválidos del archivo de libros */
char modificarLibro(Libro libro); /* Modifica el libro en el archivo */
char guardarReporte(); /* Genera un archivo TXT con el reporte de los libros */
 
/* Función de lectura de cadenas */
int leecad(char *cad, int n);
 
/* Titular del programa */
void tituloPrincipal();
 
char linea[CaracteresMaximos];



int main()
{
	setlocale(LC_ALL, "spanish"); /* Permite imprimir caracteres con tilde */
  Login();
 
	return 0;
}
 
void menuPrincipal(string tipoUsuario)
{
	char repite = 1;
	int opcion = -1;
	/* Cuando el usuario ingresa texto en lugar de ingresar una opción. El programa no modifica
	el valor de opcion. En ese caso, no se debe de ingresar a ninguno de los case, por eso se está
	inicializando la variable opcion con un valor que no permita ejecutar ningún case. Simplemente,
	volver a interar y pedir nuevamente la opción. */
 
	do {
		system(CLEAR);
 
		tituloPrincipal();
 
		printf("\n\t\t\t\t\t\t\t\t MENU PRINCIPAL\n");
    
		printf("\n\t\t[1]. Registrar Nuevo Libro \n");


		printf("\t\t[2]. Reporte de libros\n");

    // 3. También quiere mostrar la información bibliográfica referente a un libro en concreto que haya en el inventario.
		printf("\t\t[3]. Buscar información bibliografica por ID\n");

    // Nueva Compra
		printf("\t\t[4]. Modificar Libro\n");
		//printf("\t\t[5]. Eliminación registros\n");
		printf("\t\t[5]. Salir\n");
		printf("\n\t\tIngrese su opción: [ ]\b\b");
 
		/* Lectura segura de un entero */
		leecad(linea, CaracteresMaximos);
		sscanf(linea, "%d", &opcion);
 
		switch (opcion) {
 
			case 1:
				menuInsertar();
				break;
 
			case 2:
        if(tipoUsuario == "Propietario"){
				  menuMostrar();
        }else{
		      printf("\n\t\tNo tienes permiso para esta acción\b\b");
        }
				break;
 
			case 3:
				menuBuscar();
				break;
 
			case 4:
				menuModificar();
				break;
 
			case 5:
				repite = 0;
        Login();
				break;
		}
 
	} while (repite);
}

void Login() {
  string Usuarios[4][3] = 
  {{"Maria", "123", "Propietario"}, 
  {"Diego", "456", "Propietario"}, 
  {"Javier", "abc", "Operador"}, 
  {"Luisa", "cde", "Operador"}};

  while (true) {
    system(CLEAR);

    printf("\n     ============================================\n");
    printf("\t\t\t\t\t\tLOGIN\n");
    printf("     ============================================\n");

    string Usuario, Contrasena;
    int j = 0;

    cout << "\n\tUsuario: ";
    getline(cin, Usuario);
    cout << "\tPassword: ";
    getline(cin, Contrasena);

    string Opcion;

    for (int i = 0; i <= 3; i++) {
      if (Usuarios[i][0] == Usuario && Usuarios[i][1] == Contrasena) {
        menuPrincipal(Usuarios[i][2]);
      }
      else {
        j++;

        if (j == 2) {
          cout << "\n\t\t¡ACCESO DENEGADO!";

          printf("\n\t\t Ingrese cualquier caracter para continuar ");
          printf("\n\t\t O ingrese 's' para salir: [ ]\b\b");

          getline(cin, Opcion);
        }
      }
    }

    if (Opcion == "S" || Opcion == "s"){
      break;
    }
  }
}
// -------------------------------------

void menuInsertar()
{
	Libro libro;
	int codigo = 0;
	char repite = 1;
	char respuesta[CaracteresMaximos];
 
	do {
		system(CLEAR);
		tituloPrincipal();
		printf("\n\t\t\t==| REGISTRAR NUEVO LIBRO |==\n");
 
		/* Se pide el código del libro a insertar */
		printf("\n\tCódigo del libro: ");
		leecad(linea, CaracteresMaximos);
		sscanf(linea, "%d", &codigo);
 
		/* Se verifica que el libro no haya sido almacenado anteriormente */
		if (!existeLibro(codigo, &libro)) {
 
			libro.codigo = codigo;
 
			/* Se piden los demás datos del libro a insertar */
			printf("\tNombre del libro: ");
			leecad(libro.titulo, CaracteresMaximos);

        // int cantidad;
        // bool estado; //agregado

			printf("\tApellido del autor: ");
			leecad(libro.apellidoAutor, CaracteresMaximos);
      
      printf("\tNombre del autor: ");
			leecad(libro.nombreAutor, CaracteresMaximos);
 
			printf("\tCosto del libro (Q): ");
			leecad(linea, CaracteresMaximos);
			sscanf(linea, "%lf", &libro.costo);

      printf("\tEditoral del Libro: ");
			leecad(libro.editorial, CaracteresMaximos);

      printf("\tTipo de Libro: ");
			leecad(libro.tipo, CaracteresMaximos);

      printf("\tFecha de Copyright: ");
			leecad(libro.fecha, CaracteresMaximos);
 
			printf("\tCantidad: ");
			leecad(linea, CaracteresMaximos);
			sscanf(linea, "%d", &libro.cantidad);

      printf("\tEstado: ");
			leecad(libro.estado, CaracteresMaximos);
 
			/* Se inserta el libro en el archivo */
			if (insertarLibro(libro)) {
				printf("\n\tEl libro fue registrado correctamente\n");
 
			} else {
				printf("\n\tOcurrió un error al intentar registrar el libro\n");
			}
		} else {
			/* El libro ya existe, no puede ser insertado. */
			printf("\n\tEl libro de código %d ya existe.\n", codigo);
		}
 
		printf("\n\tDesea seguir ingresando libros? [S/N]: ");
		leecad(respuesta, CaracteresMaximos);
 
		if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
			repite = 0;
		}
 
	} while (repite);
}

void menuBuscar()
{
	Libro libro;
	int codigo;
	char repite = 1;
	char respuesta[CaracteresMaximos];
 
	do {
		system(CLEAR);
		tituloPrincipal();
		printf("\n\t\t\t==| BUSCAR LIBRO POR REFERENCIA BIBLIOGRAFICA |==\n");
 
		/* Se pide el código del libro a buscar */
		printf("\n\tCódigo de libro: ");
		leecad(linea, CaracteresMaximos);
		sscanf(linea, "%d", &codigo);
 
		/* Se verifica que el libro a buscar, exista */
		if (existeLibro(codigo, &libro)) {
 
			/* Se muestran los datos del libro */
			printf("\n\tCódigo del libro: %d\n", libro.codigo);
			printf("\tTitulo del libro: %s\n", libro.titulo);
			printf("\tNombre del autor: %s\n", libro.nombreAutor);
			printf("\tApellido del autor: %s\n", libro.apellidoAutor);				
			printf("\tEditorial: %s\n", libro.editorial);				
      printf("\tTipo del libro: %s\n", libro.tipo);
      printf("\tFecha de Copyright: %s\n", libro.fecha);
 
		} else {
			/* El libro no existe */
			printf("\n\tEl libro con referncia bibliografica %d no existe.\n", codigo);
		}
 
		printf("\n\tDesea seguir buscando algún otro libro? [S/N]: ");
		leecad(respuesta, CaracteresMaximos);
 
		if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
			repite = 0;
		}
 
	} while (repite);
}

// -------------------------------------

 
void menuMostrar()
{
	Libro *libros;
	int numeroLibros;
	int i, j, temp;
	float costoTotal;
	int cantidadTotal;
	char respuesta[CaracteresMaximos];
 
	system(CLEAR);
	tituloPrincipal();
	libros = obtenerLibros(&numeroLibros); /* Retorna un vector dinámico de libros */

 
	if (numeroLibros == 0) {
		printf("\n\tEl archivo está vacío!!\n");
		getchar();
 
	// int codigo;
	// char titulo[CaracteresMaximos]; //agregado
	// double costo; //Antes era float
	// char editorial[CaracteresMaximos]; //agregado
	// int cantidad;

	} else {
		printf("\n\t\t    ==| LISTADO DE LIBROS REGISTRADOS |==\n");
		printf(" ------------------------------------------------------------------------------\n");
		printf("%8s\t%-20s%15s%15s%10s\n", "CODIGO", "TITULO", "COSTO Q", "CANTIDAD", "EDITORIAL");
		printf(" ------------------------------------------------------------------------------\n");

    cout << endl;
 
		/* Se recorre el vector dinámico de libros */
		for (i = 0; i < numeroLibros; i++) {
			if (libros[i].codigo != valorCent) {
        
        printf("%7d \t %-20.20s %.2lf %5d %20s\n", libros[i].codigo, libros[i].titulo, libros[i].costo, libros[i].cantidad, libros[i].editorial);
			}
		}
		printf(" ------------------------------------------------------------------------------\n");

    vector<string> arr = { "raid", "implementation", "states", "all",
                           "the", "requirements", "parameter", "a",
                           "and", "or", "execution", "participate" };
 
		printf("\n\tDesea guardar el reporte en un archivo de texto? [S/N]: ");
		leecad(respuesta, CaracteresMaximos);
 
		if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
			if (guardarReporte()) {
				printf("\n\tEl reporte fue guardado con éxito\n");
			} else {
				printf("\n\tOcurrió un error al guardar el reporte\n");
			}
 
			getchar();
		}
	}
}
 
void menuModificar()
{
	Libro libro;
	int codigo;
	char repite = 1;
	char respuesta[CaracteresMaximos];
 
	do {
		system(CLEAR);
		tituloPrincipal();
		printf("\n\t\t\t==| Venta de LIBRO POR CÓDIGO |==\n");
 
		/* Se pide el código del libro a modificar */
		printf("\n\tCódigo de libro: ");
		leecad(linea, CaracteresMaximos);
		sscanf(linea, "%d", &codigo);
 
		/* Se verifica que el libro a buscar exista */
		if (existeLibro(codigo, &libro)) {
 
			/* Se muestran los datos del libro */
			printf("\tCantidad: %d\n", libro.cantidad);
 
 			
			/* Modificación de la cantidad del libro */
			printf("\n\tCantidad del libro actual: %d\n", libro.cantidad);
			printf("\tDesea modificar la cantidad del libro? [S/N]: ");
			leecad(respuesta, CaracteresMaximos);
			if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {

      	Compra compra;

				printf("\tNueva cantidad del libro: ");
				leecad(linea, CaracteresMaximos);
				sscanf(linea, "%d", &libro.cantidad);
			}
 
			printf("\n\tEstá seguro que desea modificar los datos del libro? [S/N]: ");
			leecad(respuesta, CaracteresMaximos);
 
			if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
				/* Se modifica el libro en el archivo */
          if(libro.cantidad==0){
            if (eliminarLibro(codigo)) {
            printf("\n\t Libro eliminado satisfactoriamente.\n");
          } else {
            printf("\n\tEl libro no pudo ser eliminado\n");
          }
        }else{
          if (modificarLibro(libro)) {
					printf("\n\tEl libro fue modificado correctamente\n");
 
				  } else {
					  printf("\n\tOcurrió un error al intentar modificar el libro\n");
					  printf("\tInténtelo mas tarde\n");
				  }
        }
			}
		} else {
			/* El libro no existe */
			printf("\n\tEl libro de código %d no existe.\n", codigo);
		}
 
		printf("\n\tDesea modificar algún otro libro? [S/N]: ");
		leecad(respuesta, CaracteresMaximos);
 
		if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
			repite = 0;
		}
 
	} while (repite);
}
 
void menuEliminarFisica()
{
	char respuesta[CaracteresMaximos];
 
 
	system(CLEAR);
	tituloPrincipal();
	printf("\n\t\t==> ELIMINAR FÍSICAMENTE REGISTROS DEL ARCHIVO <==\n");
 
	/* Se pide el código del libro a eliminar */
	printf("\n\tSeguro que desea proceder con la eliminación física? [S/N]: ");
	leecad(respuesta, CaracteresMaximos);
 
	if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
		if (eliminacionFisica()) {
			printf("\n\tLa eliminación física se realizó con éxito.\n");
		} else {
			printf("\n\tOcurrió algún error en la eliminación física.\n");
		}
 
		getchar();
	}
}
 
Libro *obtenerLibros(int *n)
{
	FILE *archivo;
	Libro libro;
	Libro *libros; /* Vector dinámico de libros */
	int i;
 
	/* Abre el archivo en modo lectura */
	archivo = fopen("libros.dat", "rb");
 
	if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
		*n = 0; /* No se pudo abrir. Se considera n  */
		libros = NULL;
 
	} else {
 
		fseek(archivo, 0, SEEK_END); /* Posiciona el cursor al final del archivo */
		*n = ftell(archivo) / sizeof(Libro); /* # de libros almacenados en el archivo. (# de registros) */
		libros = (Libro *)malloc((*n) * sizeof(Libro)); /* Se reserva memoria para todos los libros almacenados en el archivo */
 
		/* Se recorre el archivo secuencialmente */
		fseek(archivo, 0, SEEK_SET); /* Posiciona el cursor al principio del archivo */
		fread(&libro, sizeof(libro), 1, archivo);
		i = 0;
		while (!feof(archivo)) {
			libros[i++] = libro;
			fread(&libro, sizeof(libro), 1, archivo);
		}
 
		/* Cierra el archivo */
		fclose(archivo);
	}
 
	return libros;
}
 
char existeLibro(int codigoLibro, Libro *libro)
{
	FILE *archivo;
	char existe;
 
	/* Abre el archivo en modo lectura */
	archivo = fopen("libros.dat", "rb");
 
	if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
		existe = 0;
 
	} else {
		existe = 0;
 
		/* Se busca el libro cuyo código coincida con codigoLibro */
		fread(&(*libro), sizeof(*libro), 1, archivo);
		while (!feof(archivo)) {
			if ((*libro).codigo == codigoLibro) {
				existe = 1;
				break;
			}
			fread(&(*libro), sizeof(*libro), 1, archivo);
		}
 
		/* Cierra el archivo */
		fclose(archivo);
	}
 
	return existe;
}
 
char insertarLibro(Libro libro)
{
	FILE *archivo;
	char insercion;
 
	/* Abre el archivo para agregar datos al final */
	archivo = fopen("libros.dat", "ab");	/* Añade datos al final. Si el archivo no existe, es creado */
 
	if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
		insercion = 0;
 
	} else {
		fwrite(&libro, sizeof(libro), 1, archivo);
		insercion = 1;
 
		/* Cierra el archivo */
		fclose(archivo);
	}
 
	return insercion;
}
 
/* ELiminación lógica de un registro */
char eliminarLibro(int codigoLibro)
{
	FILE *archivo;
	FILE *auxiliar;
	Libro libro;
	char elimina;
 
	/* Abre el archivo para leer */
	archivo = fopen("libros.dat", "r+b");	/* Modo lectura/escritura. Si el archivo no existe, es creado */
 
	if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
		elimina = 0;
 
	} else {
 
		elimina = 0;
		fread(&libro, sizeof(libro), 1, archivo);
		while (!feof(archivo)) {
			if (libro.codigo == codigoLibro) {
				fseek(archivo, ftell(archivo) - sizeof(libro), SEEK_SET);
				libro.codigo = valorCent;
				fwrite(&libro, sizeof(libro), 1, archivo);
				elimina = 1;
				break;
			}
			fread(&libro, sizeof(libro), 1, archivo);
		}
 
		/* Cierra el archivo */
		fclose(archivo);
	}
 
	return elimina;
}
 
char eliminacionFisica()
{
	FILE *archivo;
	FILE *temporal;
	Libro libro;
	char elimina = 0;
 
	archivo = fopen("libros.dat", "rb");
	temporal = fopen("temporal.dat", "wb");
 
	if (archivo == NULL || temporal == NULL) {
		elimina = 0;
	} else {
		/* Se copia en el archivo temporal los registros válidos */
		fread(&libro, sizeof(libro), 1, archivo);
		while (!feof(archivo)) {
			if (libro.codigo != valorCent) {
				fwrite(&libro, sizeof(libro), 1, temporal);
			}
			fread(&libro, sizeof(libro), 1, archivo);
		}
		/* Se cierran los archivos antes de borrar y renombrar */
		fclose(archivo);
		fclose(temporal);
 
		remove("libros.dat");
		rename("temporal.dat", "libros.dat");
 
		elimina = 1;
	}
 
	return elimina;
}
 
char modificarLibro(Libro libro)
{
	FILE *archivo;
	char modifica;
	Libro libro2;
 
	/* Abre el archivo para lectura/escritura */
	archivo = fopen("libros.dat", "rb+");
 
	if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
		modifica = 0;
 
	} else {
		modifica = 0;
		fread(&libro2, sizeof(libro2), 1, archivo);
		while (!feof(archivo)) {
			if (libro2.codigo == libro.codigo) {
				fseek(archivo, ftell(archivo) - sizeof(libro), SEEK_SET);
				fwrite(&libro, sizeof(libro), 1, archivo);
				modifica = 1;
				break;
			}
			fread(&libro2, sizeof(libro2), 1, archivo);
		}
 
		fclose(archivo);
	}
 
	/* Cierra el archivo */
	return modifica;
}
 
char guardarReporte()
{
	FILE *archivo;
	char guardado;
	Libro *libros;
	int numeroLibros;
	int i;
	float costoTotal;
	float precioTotal;
	int cantidadTotal;
 
	libros = obtenerLibros(&numeroLibros); /* Retorna un vector dinámico de libros */
 
	if (numeroLibros == 0) {
		guardado = 0;
 
	} else {
		/* Abre el archivo en modo texto para escritura */
		archivo = fopen("libros.txt", "w");
 
		if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
			guardado = 0;
 
		} else {

			fprintf(archivo, "\n\t\t    ==| LISTADO DE LIBROS REGISTRADOS |==\n");
			fprintf(archivo, " ------------------------------------------------------------------------------\n");
			fprintf(archivo, "%8s\t%-20s%15s%15s%10s\n", "CODIGO", "TITULO", "COSTO Q", "CANTIDAD", "EDITORIAL");
			fprintf(archivo, " ------------------------------------------------------------------------------\n");
 
			/* Se recorre el vector dinámico de libros */
			costoTotal = 0;
		cantidadTotal = 0;
		for (i = 0; i < numeroLibros; i++) {
			if (libros[i].codigo != valorCent) {
					fprintf(archivo, "%7d \t%-20.20s%15.1f%5d%20s\n", libros[i].codigo, libros[i].titulo, libros[i].costo, libros[i].cantidad, libros[i].editorial);
				costoTotal += libros[i].costo;
				cantidadTotal += libros[i].cantidad;
			}
		}
			fprintf(archivo, " ------------------------------------------------------------------------------\n");
 
			guardado = 1;
 
			/* Cierra el archivo */
			fclose(archivo);
		}
	}
	
	free(libros);
	libros = NULL;
 
	return guardado;
}
 
int leecad(char *cad, int n)
{
	int i, c;
  
	/* 1 COMPROBACIÓN DE DATOS INICIALES EN EL BUFFER */

	c = getchar();
	if (c == EOF) {
		cad[0] = '\0';
		return 0;
	}

	if (c == '\n') {
		i = 0;
	} else {

		cad[0] = c;
		i = 1;
	}
 
	/* 2. LECTURA DE LA CADENA */

	for (; i < n - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
		cad[i] = c;
	}
	cad[i] = '\0';
 
	/*3. LIMPIEZA DEL BUFFER */
 
	/* Finalmente limpiamos el buffer si es necesario */
	if (c != '\n' && c != EOF) /* es un caracter */
		while ((c = getchar()) != '\n' && c != EOF);
 
 
	return 1;
}
 
void tituloPrincipal()
{
	int i;
	printf("\n     ======================================================================\n");
	printf("\t\t\t\t\t\t      LIBRERIA EL ESTUDIANTE \n");
	printf("\t\t\t Creación, reportes, eliminación, búsqueda y actualización\n");
	printf("     ======================================================================\n");
 
	i = 0;
	putchar('\n');
	for (; i < 80; i++) {
		putchar('_');
	}
}


