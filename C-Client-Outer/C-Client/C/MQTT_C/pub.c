#include <stdio.h>
#include "MQTTClient.h"

int main()
{
    MQTTClient cliente; // declarando 'objeto' cliente
    char *url_broker = "https://mqtt.eclipseprojects.io/";
    char *id_cliente = "sensor";
    int checagem = 0;
    char *mensagem = "msg!";
    int qos = 0;
    int contador_mensagem = 0;

    printf("alo!");

    checagem = MQTTClient_create(&cliente, url_broker, id_cliente, MQTTCLIENT_PERSISTENCE_NONE, NULL); // criação de um cliente, que conecatara

    // especificando parametros para conexao
    MQTTClient_connectOptions opcoes_de_conexao = MQTTClient_connectOptions_initializer;
    opcoes_de_conexao.keepAliveInterval = 10;
    opcoes_de_conexao.cleansession = 1;

    if((checagem = MQTTClient_connect(cliente, &opcoes_de_conexao)) != 0)
    {
        printf("não deu para conectar");
    }

    while (contador_mensagem < 25)
    {
        checagem = MQTTClient_publish(cliente, "topico_teste", sizeof(mensagem), mensagem, qos, 0, NULL);
        contador_mensagem++;
    }

    printf("Execucao terminada!\n");
}
