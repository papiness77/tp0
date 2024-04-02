#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* clave;

	t_log* logger;
	t_config* config;
	t_log_level info = LOG_LEVEL_INFO;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	logger = log_create("tp0.log", "primi", true, info);
	if(logger == NULL){
		printf("Error logger");
		exit(1);
	}

	log_info(logger, "Hola soy un log");

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();
	config = config_create("cliente.config");
	if(config == NULL){
		printf("Error config");
		exit(1);
	}

	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PUERTO");
	clave = config_get_string_value(config, "CLAVE");


	log_info(logger, ip);log_info(logger, puerto);log_info(logger, clave);

	//leer_consola(logger);
	
	conexion = crear_conexion(ip, puerto);

	enviar_mensaje(clave, conexion);
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;
	while(true){
	leido = readline(">");
	if(!strncmp(leido, "exit", 4)){
		printf("SALIMOS");
        free(leido);
        break;
    }
	log_info(logger, leido);
	
	free(leido);
	
	}
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;
	t_buffer* buffer;

	paquete = crear_paquete();
	if(paquete == NULL){
		printf("No se puedo crear paquete");
		exit(1);
	}
	buffer = crear_buffer(paquete);
	if(buffer == NULL){
		printf("No se puedo crear buffer");
		exit(1);
	}
	leido = readline("<");

	agregar_a_paquete(paquete, leido, sizeof(leido)+1);
	free(leido);
	enviar_paquete(paquete, conexion);	

	eliminar_paquete(paquete);
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	liberar_conexion(conexion);
	config_destroy(config);
	log_destroy(logger);
	
	
}
