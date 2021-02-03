#include <PubSubClient.h>
#include <UIPEthernet.h>
#include <SPI.h>

int pino2 = 2;
bool estado_sensor;

//Define o endereço MAC que será ultilizado 
byte mac [] = {0x00, 0x10, 0xFA, 0x6E, 0x38, 0x4A};

//Inicia o cliente Ethernet
EthernetClient client;

//Inicia o cliente MQTT
PubSubClient mqttClient(client);

//Variável utilizada para enviar as mensagens utilizando o cliente MQTT
bool mensagem;

void setup()
{

     pinMode(pino2,INPUT_PULLUP);
   
    //Inicia o controlador Ethernet e solicita um IP para um servidor de DHCP
    Ethernet.begin(mac);

    //Inicia o monitor Serial 
    Serial.begin(9600);

    //Define o IP e Porta TCP do Broker MQTT que vamos utilizar 
    mqttClient.setServer("3.82.94.158", 1883);

    //Exibe no Monitor Serial as informações sobre o IP do Arduino
    Serial.print("O IP do Arduino e: ");
    Serial.println(Ethernet.localIP());

    //Exibe no Monitor Serial as informações sobre a Máscara de Rede do Arduino
    Serial.print("A mascara de Rede do Arduino e: ");
    Serial.println(Ethernet.subnetMask());

    //Exibe no Monitor Serial as informações sobre Gateway do Arduino
    Serial.print("O Gateway do Arduino e: ");
    Serial.println(Ethernet.gatewayIP());

    //Exibe uma linha em branco
    Serial.println("");

}

void loop()
{
    //Define o nome do cliente MQTT e efetua a conexão com o servidor
    mqttClient.connect("Aecio");

    /*
    Variavel que envia a mensagem e armazena o valor de '1' caso 
    a mensagem seja enviada com sucesso e '0' caso o envio falhe
    */
    if(estado_sensor == 0)
    {
         mensagem = mqttClient.publish("aecio-t_sensor", "O RACK ESTA FECHADO!");
    }
    else
    {
         mensagem = mqttClient.publish("aecio-t_sensor", "O RACK ESTA ABERTO!");
    }

    mqttClient.loop(); //Comunicação continua entre o cliente e o Servidor MQTT


}



