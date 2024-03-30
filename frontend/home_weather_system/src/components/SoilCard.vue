<template>
  
    <v-container>
      <v-card class="mx-auto" max-width="368" rounded="lg">
        <v-row>
          <v-col>
            <v-card-title> {{title}} </v-card-title>
            <v-card-subtitle>
              <strong style="font-size: 20px;">{{data}}</strong>
              </v-card-subtitle>
            <v-card-actions>
              <v-btn> Percentage </v-btn>
            </v-card-actions>
          </v-col>
          <v-col>
              <v-icon color="black" size="80" > mdi-percent-outline </v-icon>

          </v-col>
        </v-row>
      </v-card>
    </v-container>

</template>

<script setup>

  defineProps({
      title: String,
      data : Number,
  })


</script>
