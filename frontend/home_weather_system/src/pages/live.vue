<script setup>
    import { ref , onMounted ,onUnmounted , watch } from 'vue'
    import {useMqttStore} from '@/stores/mqtt_store';
    import {storeToRefs} from 'pinia'

    const store = useMqttStore()

    const cardData = ref([0,0,0,0,0,0])
    const icons = ref(['mdi-account'])
    const tags = ref([true,false])
    const data = ref([])
    const data3 = ref([])
    const data2 = ref([])
    const label = ref([])

    const titles = ref(['Temperature' , 'Heat Index' ,  'Humidity' , 'Soil Moisture' , 'Altitude' , 'Pressure'])

    const data4 = ref([])
    const data5 = ref([])

    onMounted(()=>{
        
        store.connect()
    })

    onUnmounted(()=>{
        store.disconnect()

    })

    watch((store.newCardData), (oldvalue)=> {
        if(oldvalue.value.temperature!=undefined){
            let x = store.newCardData.value.temperature;
            let humidity = store.newCardData.value.humidity;
            let heatIndex = store.newCardData.value['heat index']
            cardData.value[0] = x
            cardData.value[1] = heatIndex
            cardData.value[2] = humidity
            cardData.value[3] = store.newCardData.value['soil moisture']
            cardData.value[4] = store.newCardData.value['altitude']
            cardData.value[5] = store.newCardData.value['pressure']

                let s = []
                for(let i in data.value){
                    s.push(data.value[i])
                }
                if(s.length==10){
                    s.shift()
                    s.push(x)
                }else{
                    s.push(x)
                }
                data.value = s
                console.log(data.value)

                let t = []
                for(let i in data3.value){
                    t.push(data3.value[i])
                }
                t.push(humidity)
                data3.value = t

                let f = []
                for(let i in data2.value){
                    f.push(data2.value[i])
                }
                if(f.length==10){
                    f.shift()
                    f.push(heatIndex)
                }else{
                    f.push(heatIndex)
                }
                data2.value = f
                console.log(data2.value)

                let d = []
                for(let i in label.value){
                    d.push(label.value[i])
                }
                if(d.length==10){
                    d.shift()
                    let currentTime = new Date()
                    let time = currentTime.getHours() + ":" + currentTime.getMinutes() + ":" + currentTime.getSeconds()
                    d.push(time)
                }else{
                    let currentTime = new Date()
                    let time = currentTime.getHours() + ":" + currentTime.getMinutes() + ":" + currentTime.getSeconds()
                    d.push(time)
                }
                label.value = d

                let s2 = []
                for(let i in data4.value){
                    s2.push(data4.value[i])
                }
                if(s2.length==10){
                    s2.shift()
                    s2.push(store.newCardData.value['altitude'])
                }else{
                    s2.push(store.newCardData.value['altitude'])
                }
                data4.value = s2
                console.log(data4.value)

                let t2 = []
                for(let i in data5.value){
                    t2.push(data5.value[i])
                }
                if(t2.length==10){
                    t2.shift()
                    t2.push(store.newCardData.value['pressure'])
                }else{
                    t2.push(store.newCardData.value['pressure'])
                }
                data5.value = t2            
        }
    })
    
  </script>

<template>
            <v-card rounded="sm" max-width="100%" style="margin-bottom: 20px;">  <v-card-title> Hello World</v-card-title></v-card>

    <v-container> 
        
                <v-row> 
                    <v-col> <TempCard :title="titles[0]" :data="cardData[0]"/> </v-col>
                    <v-col> <TempCard :title="titles[1]" :data="cardData[1]"/> </v-col>
                    <v-col> <HuCard :title="titles[2]" :data="cardData[2]"/> </v-col>

                </v-row>
                <v-row> 
                    <v-col> <SoilCard :title="titles[3]" :data="cardData[3]"/> </v-col>
                    <v-col> <AltCard :title="titles[4]" :data="cardData[4]"/> </v-col>
                    <v-col> <PressureCard :title="titles[5]" :data="cardData[5]"/> </v-col>
                    
                    
                 </v-row>
                 <LineChart :firstData="data"  :secondData="data2" :thirdData="data3"
                    title="GRAPH OF TEMPERATURE, HEAT INDEX & HUMIDITY" canvas="canvas1" 
                        :label="label"/>
                 <APLineGraph :firstData="data4"  :secondData="data5" 
                    title="GRAPH OF ALTITUDE & PRESSURE  " canvas="canvas2" 
                        :label="label"/>

    
                
                 <!-- <LineChart :data="data" title="First graph" canvas="canvas2"/>  -->
                 
   </v-container>

  </template>
  
  

  <style scoped>
.shift-left {
  margin-left: 40px; /* Adjust this value as needed */
}
</style>