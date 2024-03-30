<template>
  
    <v-container>
      <v-card class="mx-auto" max-width="368" rounded="lg">
        <v-row>
          <v-col>
            <v-card-title> {{title}} </v-card-title>
            <v-card-subtitle>
              <strong style="font-size: 20px;">{{displayData}}</strong>
              </v-card-subtitle>
            <v-card-actions>
              <v-btn @click="toggle"> Toggle </v-btn>
            </v-card-actions>
          </v-col>
          <v-col>
              <v-icon v-if="!celsius" color="black" size="80" > mdi-temperature-fahrenheit </v-icon>
              <v-icon v-else color="black" size="80" > mdi-temperature-celsius </v-icon>
              
          </v-col>
        </v-row>
      </v-card>
    </v-container>

</template>

<script setup>
  import { ref , watch} from 'vue'

  const celsius = ref(true)
  const inCelsius = ref(true)
  const f = ref(false)

  function toggle(){
    celsius.value = !celsius.value
    f.value = !f.value
    if(!f.value && celsius.value){
      inCelsius.value = true
    }else{
      inCelsius.value = false
    }

    if(!celsius.value && f.value ){
        displayData.value = ((displayData.value * 9/5) + 32).toFixed(2)
    }else{
        if(celsius.value && !f.value ){
            displayData.value = ((displayData.value - 32) * 5/9).toFixed(2)
        }   
    }
  }

  const props = defineProps({
      title: String,
      data : Number,
  })

  const displayData = ref(props.data);

  watch(() => props.data, (newVal) => {
    if(!celsius.value && f.value ){
        newVal = (newVal * 9/5) + 32
    }
    displayData.value = Number(newVal).toFixed(2)
  })

</script>
