<script setup>
    import { ref , onMounted ,onUnmounted , watch } from 'vue'
    import {useMqttStore} from '@/stores/mqtt_store';
    import {useAppStore} from '@/stores/appStore';

     import {storeToRefs} from 'pinia'

    const store = useAppStore()

    const startDate = ref(null)
    const showDatePicker = ref(false)

    const endDate = ref(null)
    const showEndDatePicker = ref(false)

    const cardData = ref([0,0,0,0,0,0])
    const icons = ref(['mdi-account'])
    const tags = ref([true,false])

    const data = ref([])
    const data1 = ref([])
    const data2 = ref([])
    const label = ref([])

    const titles = ref(['Temperature' , 'Heat Index' ,  'Humidity'])
 
    onMounted(()=>{
                
    })

    onUnmounted(()=>{
        // store.disconnect()

    })

    watch((store.data1), (oldvalue)=> {
        console.log(store.data1.value)
    })

    function formatDate(date) {
      const d = new Date(date);
      const day = d.getDate().toString().padStart(2, '0');
      const month = (d.getMonth() + 1).toString().padStart(2, '0'); // Months are 0-based
      const year = d.getFullYear().toString().slice(-2); // Get last two digits of year
      return `${day}/${month}/${year}`;
    }

    function get_timeStamp(date){
        return date.getTime()
    }


  </script>

<template>
            <v-card rounded="sm" max-width="100%" style="margin-bottom: 20px;">  <v-card-title> Hello World</v-card-title></v-card>

    <v-container> 
        
                <v-row> 
                    <v-col> <TempCard :title="titles[0]" :data="store.temp.toFixed(2)"/> </v-col>
                    <v-col> <TempCard :title="titles[1]" :data="store.hi.toFixed(2)"/> </v-col>
                    <v-col> <HuCard :title="titles[2]" :data="store.hum"/> </v-col>

                </v-row>
                
                <v-row>
                    <v-col> 
                        <v-card @click="showDatePicker = true"> 
                            <v-card-title> 
                                <span v-if="startDate">{{ formatDate(startDate) }}</span>
                                <span v-else>Start Date</span>
                            </v-card-title>
                            <v-dialog v-model="showDatePicker">
                                
                                <div style="display: flex; justify-content: center; align-items: center;">
    <v-date-picker v-model="startDate" @input="showDatePicker = false"></v-date-picker>
  </div>                            </v-dialog>
                        </v-card>
                    </v-col> 
                    
                    <v-col> 
                        <v-card @click="showEndDatePicker = true"> 
                            <v-card-title> 
                                <span v-if="endDate">{{ formatDate(endDate) }}</span>
                                <span v-else>End Date</span>
                            </v-card-title>
                            <v-dialog v-model="showEndDatePicker">
                                
                                <div style="display: flex; justify-content: center; align-items: center;">
    <v-date-picker v-model="endDate" @input="showEndDatePicker = false"></v-date-picker>
    </div>                            </v-dialog>
                        </v-card>
                    </v-col>

                       

                 
                 <!-- <APLineGraph :firstData="data4"  :secondData="data5" 
                    title="GRAPH OF ALTITUDE & PRESSURE (ANALYSIS)" canvas="canvas2" 
                        :label="label"/> -->

                    </v-row> 

                    <v-row>
                       

                         <v-col style="margin-top:30px"> 
                            <div align="center">
                        <v-btn @click="store.functions(startDate.getTime(),endDate.getTime())"> Analyze </v-btn>
                        </div>
                    </v-col>
              
                    <v-row>
                        <LineChart :firstData="store.data1"  :secondData="store.data2" :thirdData="store.data3"
                    title="GRAPH OF TEMPERATURE, HEAT INDEX & HUMIDITY (ANALYSIS)" canvas="canvas1" 
                        :label="store.labels"/>
                    </v-row> 
                    </v-row>

                
                 <!-- <LineChart :data="data" title="First graph" canvas="canvas2"/>  -->
                 
   </v-container>

  </template>
  
  

  <style scoped>
.shift-left {
  margin-left: 40px; /* Adjust this value as needed */
}
</style>