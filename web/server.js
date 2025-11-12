const express = require('express');
const mqtt = require('mqtt');

const app = express();
const port = 3000;

// Servir le frontend
app.use(express.static('public'));

// Connexion au broker MQTT
const client = mqtt.connect('wss://broker.emqx.io:8084/mqtt', {
    username: 'Antho' 
});

client.on('connect', () => {
    console.log('Connecté au broker MQTT');

    // S'abonner au topic
    client.subscribe('RadarB2Ynov', (err) => {
        if (!err) console.log('Abonné au topic RadarB2Ynov');
        else console.error('Erreur d\'abonnement :', err);
    });
});

// Recevoir les messages
client.on('message', (topic, message) => {
    console.log(`Message reçu sur ${topic}: ${message.toString()}`);
});

// Démarrer le serveur web
app.listen(port, () => {
    console.log(`Serveur web lancé sur http://localhost:${port}`);
});
