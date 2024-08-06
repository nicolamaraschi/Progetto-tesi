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
  res.sendFile('menu.html', { root: publicPath });
});

app.get('/turnOn0', async (req, res) => {
  console.log('Ricevuta richiesta per accendere tutte le resistenze');
    try {
      await axios.get('http://172.20.10.8/turnOn0');
      //res.send('Turned On 1');
    } catch (error) {
      console.error('Non riesco a contattare ESP8266: per accensione di tutte le resistenze:', error.message);
      res.status(500).send('Internal Server Error');
    }
  });

app.get('/turnOn1', async (req, res) => {
  console.log('Ricevuta richiesta per accendere 1');
    try {
      await axios.get('http://172.20.10.8/turnOn1');
      //res.send('Turned On 1');
    } catch (error) {
      console.error('Error turning On 1:', error.message);
      res.status(500).send('Internal Server Error');
    }
  });
  
  app.get('/turnOn2', async (req, res) => {
    try {
      await axios.get('http://172.20.10.8/turnOn2');
      //res.send('Turned On 2');
    } catch (error) {
      console.error('Error turning On 2:', error.message);
      res.status(500).send('Internal Server Error');
    }
  });
  
  app.get('/turnOn3', async (req, res) => {
    try {
      await axios.get('http://172.20.10.8/turnOn3');
      //res.send('Turned On 3');
    } catch (error) {
      console.error('Error turning On 3:', error.message);
      res.status(500).send('Internal Server Error');
    }
  });
  
  
  app.get('/turnOn4', async (req, res) => {
    try {
      await axios.get('http://172.20.10.8/turnOn4');
      //res.send('Turned On 4');
    } catch (error) {
      console.error('Error turning On 4:', error.message);
      res.status(500).send('Internal Server Error');
    }
  });


  app.get('/turnOn5', async (req, res) => {
  try {
    await axios.get('http://172.20.10.8/turnOn5');
    //res.send('Turned On 5');
  } catch (error) {
    console.error('Error turning On 5:', error.message);
    res.status(500).send('Internal Server Error');
  }
});

app.get('/turnOn6', async (req, res) => {
  try {
    await axios.get('http://172.20.10.8/turnOn6');
    //res.send('Turned On 6');
  } catch (error) {
    console.error('Error turning On 6:', error.message);
    res.status(500).send('Internal Server Error');
  }
});

app.get('/turnOn7', async (req, res) => {
  try {
    await axios.get('http://172.20.10.8/turnOn7');
    //res.send('Turned On 7');
  } catch (error) {
    console.error('Error turning On 7:', error.message);
    res.status(500).send('Internal Server Error');
  }
});

app.get('/turnOn8', async (req, res) => {
  try {
    await axios.get('http://172.20.10.8/turnOn8');
    //res.send('Turned On 8');
  } catch (error) {
    console.error('Error turning On 8:', error.message);
    res.status(500).send('Internal Server Error');
  }
});

app.get('/turnOn9', async (req, res) => {
  try {
    await axios.get('http://172.20.10.8/turnOn9');
    //res.send('Turned On 9');
  } catch (error) {
    console.error('Error turning On 9:', error.message);
    res.status(500).send('Internal Server Error');
  }
});

app.get('/turnOn10', async (req, res) => {
    try {
      await axios.get('http://172.20.10.8/turnOn10');
      //res.send('Turned On 10');
    } catch (error) {
      console.error('Error turning On 10:', error.message);
      res.status(500).send('Internal Server Error');
    }
  });


  app.get('/turnOn11', async (req, res) => {
    try {
      await axios.get('http://172.20.10.8/turnOn11');
      //res.send('Turned On 11');
    } catch (error) {
      console.error('Error turning On 11:', error.message);
      res.status(500).send('Internal Server Error');
    }
  });
  
  app.get('/turnOn12', async (req, res) => {
    try {
      await axios.get('http://172.20.10.8/turnOn12');
      //res.send('Turned On 12');
    } catch (error) {
      console.error('Error turning On 12:', error.message);
      res.status(500).send('Internal Server Error');
    }
  });
  
  app.get('/turnOn13', async (req, res) => {
    try {
      await axios.get('http://172.20.10.8/turnOn13');
      //res.send('Turned On 13');
    } catch (error) {
      console.error('Error turning On 13:', error.message);
      res.status(500).send('Internal Server Error');
    }
  });
  
  app.get('/turnOn14', async (req, res) => {
    try {
      await axios.get('http://172.20.10.8/turnOn14');
      //res.send('Turned On 14');
    } catch (error) {
      console.error('Error turning On 14:', error.message);
      res.status(500).send('Internal Server Error');
    }
  });
  
  app.get('/turnOn15', async (req, res) => {
    try {
      await axios.get('http://172.20.10.8/turnOn15');
      //res.send('Turned On 15');
    } catch (error) {
      console.error('Error turning On 15:', error.message);
      res.status(500).send('Internal Server Error');
    }
  });


  app.get('/turnOn16', async (req, res) => {
    try {
      await axios.get('http://172.20.10.8/turnOn16');
      //res.send('Turned On 16');
    } catch (error) {
      console.error('Error turning On 16:', error.message);
      res.status(500).send('Internal Server Error');
    }
  });


  // Gestisci la richiesta per ottenere voltaggio mpp, corrente mpp, potenza mpp da esp9266
  app.get('/api/data', async (req, res) => {
    try {
      //console.log('Richiesta API ricevuta per i dati');
      // Effettua richieste ai tuoi endpoint API sull'ESP8266 e ottieni i dati
      const response1 = await axios.get('http://172.20.10.8/api/first');
      const response2 = await axios.get('http://172.20.10.8/api/second');
      const response3 = await axios.get('http://172.20.10.8/api/third');
  
      console.log('Richieste all\'ESP8266 completate');
      // Invia i dati al client in formato JSON
      res.json({
        voltaggio: response1.data,
        amperaggio: response2.data,
        intensita: response3.data
      });
    } catch (error) {
      console.error('Non riesco a contattare ESP8266, per i dati mpp ', error.message);
      res.status(500).send('Internal Server Error');
    }
  });



  // Endpoint per ottenere i dati dall'ESP8266 delle coppie di 16 valori di corrente e voltaggio
app.get('/api/datigrafici', async (req, res) => {
  try {
    //console.log('Richiesta API ricevuta per i dati dei grafici');

    // Effettua una richiesta all'endpoint dell'ENon riesco a contattare ESP8266, l hai acceso??:SP8266
    const response = await axios.get('http://172.20.10.8/get16Values'); // Sostituisci con l'indirizzo IP corretto dell'ESP8266

    console.log('Richiesta all\'ESP8266 completata');

    // Invia i dati al client in formato JSON
    res.json({
      values: response.data.values
    });
  } catch (error) {
    console.error('Non riesco a contattare ESP8266, per i dati dei grafici:', error.message);
    res.status(500).send('Internal Server Error');
  }
});




// Avvia il server sulla porta 3000
const PORT = 2000;
app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});
