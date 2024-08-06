const express = require('express');
const app = express();
const path = require('path');
const axios = require('axios');

// Specifica il percorso della cartella 'public'
const publicPath = path.join(__dirname, 'public');

// Servi i file statici dalla cartella 'public'
app.use(express.static(publicPath));

// Gestisci la richiesta per la pagina principale
app.get('/', (req, res) => {
  res.sendFile('index.html', { root: publicPath });
});

// Gestisci la richiesta per inviare comandi all'ESP8266
app.get('/turnOn', async (req, res) => {
  try {
    // Fai una richiesta all'API dell'ESP8266 per accendere il pin 13
    await axios.get('http://192.168.1.83/turnOn');
    res.send('Turned On');
  } catch (error) {
    console.error('Error turning on LED:', error.message);
    res.status(500).send('Internal Server Error');
  }
});

app.get('/turnOff', async (req, res) => {
  try {
    // Fai una richiesta all'API dell'ESP8266 per spegnere il pin 13
    await axios.get('http://192.168.1.83/turnOff');
    res.send('Turned Off');
  } catch (error) {
    console.error('Error turning off LED:', error.message);
    res.status(500).send('Internal Server Error');
  }
});

// Avvia il server sulla porta 3000
const PORT = 3000;
app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});
