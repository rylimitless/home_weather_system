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
              <v-btn >Absolute</v-btn>
            </v-card-actions>
          </v-col>
          <v-col>
              <v-icon  color="black" size="80" > mdi-home-thermometer </v-icon>
              
          </v-col>
        </v-row>
      </v-card>
    </v-container>

</template>

<script setup>
  import { ref , watch} from 'vue'


  const props = defineProps({
      title: String,
      data : Number,
  })

  const displayData = ref(props.data);

  watch(() => props.data, (newVal) => {
    displayData.value = newVal.toFixed(2)
  })

</script>
