google.charts.load('current', { packages: ['corechart', 'line'] });
google.charts.setOnLoadCallback(drawBasic);
var data = new Date();

let receivedData = '';
let nova = 0;
let dataTable = null;

function delay(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

document.addEventListener('DOMContentLoaded', function() {

  async function requestSerialPort() {
    try {
      const port = await navigator.serial.requestPort();
      await port.open({ baudRate: 9600 });
      console.log('Porta serial aberta com sucesso!');

      const reader = port.readable.getReader();
      while (true) {
        const { value, done } = await reader.read();
        if (done) {
          console.log('Leitura da porta serial concluída.');
          break;
        }

        const receivedString = new TextDecoder().decode(value);
        receivedData += receivedString;

        if (receivedData.endsWith('\n')) {
          nova = parseFloat(receivedData);
          let nova2 = nova;
          receivedData = '';
          await delay(500);

          const newData = [new Date(), parseFloat(nova2)]; 

          if (dataTable) {
            dataTable.addRow(newData); 
          } else {
            dataTable = new google.visualization.DataTable();
            dataTable.addColumn('date', 'Tempo');
            dataTable.addColumn('number', 'CO2');
            dataTable.addRow(newData);
          }

          drawBasic();
        }
      }
    } catch (error) {
      console.error('Erro ao acessar a porta serial:', error);
    }
  }
  
  if ('serial' in navigator) {
    const requestButton = document.getElementById('request-button');
    requestButton.addEventListener('click', requestSerialPort);
  } else {
    console.error('O Web Serial API não é suportado neste navegador.');
  }
});

function drawBasic() {
  var options = {
    hAxis: {
      title: ''
    },
    vAxis: {
      title: ''
    },
    colors: ['#8a2be2'],
    height: 700,
  };

  var chart = new google.visualization.LineChart(document.getElementById('chart_div'));

  chart.draw(dataTable, options);
}

setInterval(function() {
  drawBasic();
}, 1000);

