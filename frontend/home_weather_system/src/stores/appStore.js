import { defineStore } from "pinia";
import {ref , reactive} from 'vue'

export const useAppStore = defineStore('appstore', () => {

    const avgData = ref([])
    const temp = ref(0)
    const hum = ref(0)
    const hi = ref(0)

    const data1 = ref([])
    const data2 = ref([])
    const data3 = ref([])

    const labels = ref([])

    function functions(start,end){
        fetchAvgData(start,end)
        getAllData(start,end)
    }

    async function fetchAvgData(start , end) {
        try {
        let url = `/app/avg/${Number(start)/1000}/${Number(end)/1000}`
            console.log(url)
          const response = await fetch(url, {
          });
          if (!response.ok) {
            throw new Error(`Error fetching data: ${response.status}`);
          }
          const data = await response.json(); // Parse JSON response (if applicable)
        //   console.log(data);
           temp.value  = data.avg[0].temperature
         hum.value = data.avg[0].humidity
           hi.value = data.avg[0]['heat_index']
        //    console.log(data.avg[0])
        } catch (error) {
            console.log("Error:")
          console.error("Error:", error);
        }
      }


      async function getAllData(start,end){
        try {
            let url = `/app/data/${Number(start)/1000}/${Number(end)/1000}`
                console.log(url)
              const response = await fetch(url, {
              });
              if (!response.ok) {
                throw new Error(`Error fetching data: ${response.status}`);
              }
              const data = await response.json(); // Parse JSON response (if applicable)
             let g = []
                let h = []
                let d = []
                let y = []
                for(let i=0;i<data.data.length;i++){
                if(g.length!=10){
                    g.push(data.data[i].temperature)
                    d.push(data.data[i].humidity)
                    y.push(data.data[i].heat_index)
                    const timestamp = data.data[i].timestamp;
                    const date = new Date(timestamp);
                    const hours = date.getHours();
                    const minutes = "0" + date.getMinutes();
                    const seconds = "0" + date.getSeconds();
                    const formattedTime = hours + ':' + minutes.substr(-2) + ':' + seconds.substr(-2);
                    h.push(formattedTime)
                }
                data1.value = g
                data2.value = d
                labels.value = h
                data3.value = y
                }
            } catch (error) {
                console.log("Error:")
              console.error("Error:", error);
            }
          }
          
          console.log(`length: ${data1.value.length}`)

      return {functions , temp , hum , hi , data1,data2 , data3,  labels}

      
  })


