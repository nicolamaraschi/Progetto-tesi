// codice se desideri usare piu resistenze contemporaneamente

$(document).ready(function() {
  let index = 0; // Indice per tenere traccia della resistenza corrente

  // Funzione per accendere la resistenza successiva
  function accendiResistenza() {
    $('.btn-toggle').eq(index).addClass('active').text('On');
    // Imposta un timeout per spegnere la resistenza dopo un 1/4 secondo
    setTimeout(spegniResistenza, 250);
  }

  // Funzione per spegnere la resistenza corrente
  function spegniResistenza() {
    $('.btn-toggle').eq(index).removeClass('active').text('Off');
    index++; // Passa alla resistenza successiva
    // Se non abbiamo raggiunto la fine, accende la prossima resistenza
    if (index < $('.btn-toggle').length) {
      accendiResistenza();
    }
  }

  // Evento click sul bottone per accendere tutte le resistenze
  $('#accendiTutte').on('click', function() {
    index = 0; // Resetta l'indice
    accendiResistenza(); // Accende la prima resistenza
  });
});

  
  