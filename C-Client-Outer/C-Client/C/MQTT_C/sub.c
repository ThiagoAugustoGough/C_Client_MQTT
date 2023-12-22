/* 
    VERSÃO 1.0 - NO THREADING, SIMPLE, MQTT V 3.2 ... EVOLUIRÁ NA VERSÃO 2.0
*/
#include <stdio.h>
#include "MQTTClient.h"

int main()
{
    MQTTClient cliente; // declarando 'objeto' cliente
    char *url_broker = "https://mqtt.eclipseprojects.io/:1883"; //nao sei se precisa da porta... testar!!!!!!
    char *id_cliente = "sensor";
    int checagem = 0;
    // char *mensagem = "msg!";
    // int qos = 0;
    int contador_mensagem = 0;
    char* topico;
    char** topic_location = &topico; //nao sei se precisa apontar para o nome do topico ou para uma string vazia... testar!!!!!
    int largura_topico = 0;
    MQTTClient_message *message_received = NULL;
    unsigned int timeout = 4923;
    
    checagem = MQTTClient_create(&cliente, url_broker, id_cliente, MQTTCLIENT_PERSISTENCE_NONE, NULL); // criação de um cliente, que conecatara

    // especificando parametros para conexao
    MQTTClient_connectOptions opcoes_de_conexao = MQTTClient_connectOptions_initializer;
    opcoes_de_conexao.keepAliveInterval = 10;
    opcoes_de_conexao.cleansession = 1;

    checagem = MQTTClient_connect(cliente, &opcoes_de_conexao);
    checagem = MQTTClient_subscribe(cliente, "topico_teste", 0);
    //MQTTClient_setCallbacks();

    while (contador_mensagem <= 25)
    {
        checagem = MQTTClient_receive(cliente, topic_location, &largura_topico, &message_received, timeout);
        MQTTClient_free(NULL);
    }

        MQTTClient_freeMessage(&message_received); //acho que vai fora do loop e é chamada apos receber mensagem... must find out
        checagem = MQTTClient_disconnect(cliente, 1000);
    printf("Execucao terminada!\n");
}

//1MQTTCLIENT_TOPICNAME_TRUNCATED = -7