<template>
  
    <v-container>
      <v-card class="mx-auto" max-width="368" rounded="lg">
        <v-row>
          <v-col>
            <v-card-title> {{title}} </v-card-title>
            <v-card-subtitle>
              <strong style="font-size: 20px;">{{displayString}} </strong>
              </v-card-subtitle>
            <v-card-actions>
              <v-btn @click="toggle"> Toggle </v-btn>
            </v-card-actions>
          </v-col>
          <v-col>
            <v-icon color="black" size="80" > mdi-car-brake-low-pressure </v-icon>
              
          </v-col>
        </v-row>
      </v-card>
    </v-container>

</template>

<script setup>
  import { ref , watch} from 'vue'

  const hpa = ref(true)
  const mmHg = ref(false)

  const conversionRate = 0.750061561303
  const displayString = ref('0.00 hPa')

  function toggle(){
    hpa.value = !hpa.value
    mmHg.value = !mmHg.value
    if(hpa.value && !mmHg.value){
        displayData.value = displayData.value / conversionRate
        displayString.value = displayData.value.toFixed(2).toString() + ' hPa'
    }else{
        displayData.value = displayData.value * conversionRate  
        displayString.value = displayData.value.toFixed(2).toString() + ' mmHg'
    }
  }

  const props = defineProps({
      title: String,
      data : Number,
  })

  const displayData = ref(props.data);

  watch(() => props.data, (newVal) => {
    console.log(`hpa: ${hpa.value}, mmHg: ${mmHg.value}`)
    if(hpa.value && !mmHg.value){
        displayString.value = newVal.toFixed(2).toString() + ' hPa'
    }else{
        displayString.value = (newVal * conversionRate).toFixed(2).toString() + ' mmHg'}
  })

</script>
