<!-- <template>
  
      <v-container>
        <v-card class="mx-auto" max-width="368" rounded="lg">
          <v-row>
            <v-col>
              <v-card-title> {{title}} </v-card-title>
              <v-card-subtitle>
                <strong style="font-size: 20px;">{{displayData}}</strong>
                </v-card-subtitle>
              <v-card-actions>
                <v-btn> Toggle </v-btn>
              </v-card-actions>
            </v-col>
            <v-col>
              <v-icon v-if="!showf" color="black" size="80" > mdi-temperature-celsius</v-icon>
                <v-icon v-if="toggle" color="black" size="80" > mdi-temperature-fahrenheit </v-icon>
              <v-icon v-if="hi" color="black" size="80" > mdi-temperature-celsius </v-icon>
              <v-icon v-if="hu" color="black" size="80" > mdi-home-thermometer </v-icon>
              <v-icon v-if="so" color="black" size="80" > mdi-percent-outline </v-icon>
              <v-icon v-if="alt" color="black" size="80" > mdi-altimeter </v-icon>
              <v-icon v-if="pre" color="black" size="80" > mdi-car-brake-low-pressure </v-icon>
            
            </v-col>
          </v-row>
        </v-card>
      </v-container>

  </template>
  
  <script setup>
    import { ref } from 'vue'

    const showf = ref(false)
    const toggle = ref(false)



    const props = defineProps({
        title: String, 
        data : Number,
        tag : Boolean,
        icon : String,
        temp : Boolean,
        t : Boolean,
        alt : Boolean,
        hi: Boolean,
        hu: Boolean,
        so: Boolean, 
        pre : Boolean,
    })

   const displayData = ref(props.data);
    showf.value = toggle.value && props.temp;



  
  </script>
   -->