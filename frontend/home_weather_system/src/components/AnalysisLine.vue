<template>
    <div  style="margin-top:30px">
      <div align="center"> <h3> {{title}}</h3></div>
        <div id="chartContainer">
            <canvas :id="canvasId" class="mychart"></canvas>
        </div>
    </div>
  </template>
  
  <script setup>
  
    const props = defineProps({
      firstData : Array,
      secondData : Array,
      thirdData : Array,
      title : String,
      canvas :String,
      label : Array,
    })
  
    import Chart from 'chart.js/auto'
    import { onMounted, ref , watch} from 'vue';
  
    const canvasId = ref(props.canvas)
    const firstDataCopy = [...props.firstData];
    const secondDataCopy = [...props.secondData];
    const thirdDataCopy = [...props.thirdData];
  
    let myChart = null;
  
    watch(() => props.firstData, (newData) => {
      console.log(`this is the data of temperature ${newData}`) // log new data
      if(myChart){
        myChart.data.datasets[0].data = newData;
        myChart.update(); // Update the chart
      }
    })
  
    watch(() => props.secondData, (newData) => {
      if(myChart){
        myChart.data.datasets[1].data = newData;
        myChart.update(); // Update the chart
      }
    })
  
    watch(() => props.thirdData, (newData) => {
      console.log(`this is the data of humidity ${newData}`) // log new data
  
      if(myChart){
        myChart.data.datasets[2].data = newData;
        myChart.update(); // Update the chart
      }
    })
    
    
    watch(() => props.label, (newData) => {
      if(myChart){
        myChart.data.labels = newData;
        myChart.update(); // Update the chart
      }
    })
  
    onMounted(() => {
      createChart()
    });
  
    function createChart() {
      const ctx = document.getElementById(props.canvas);
      myChart = new Chart(ctx, {
        type: 'line',
        data: {
          labels: [],
          datasets: [{
            label: 'Temperature',
            data: firstDataCopy,
            borderWidth: 3
          },
          {
            label: 'Heat Index',
            data: secondDataCopy,
            borderWidth: 3
          },
          {
            label: 'Humidity',
            data: thirdDataCopy,
            borderWidth: 3
          },
          
        ]
        },
        options: {
          responsive: true,
          plugins: {
            legend: {
              position: 'top',
            },
            title: {
              display: true,
              text: ''
            }
          }
        }
      });
    }
  </script>
  
  <style scoped>
  .chart-container {
    width: 100px; /* Adjust as needed */
    height: 100px; /* Adjust as needed */
    /* margin: auto; */
    padding: 20px;
    /* box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); */
  }
  .myChart {
    width: 100%;
    height: 100%;
  }
  </style>