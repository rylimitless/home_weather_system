<template>
  <v-app-bar :elevation="1">
    <v-spacer></v-spacer>
    <v-btn  class ="buttons" :to="'/'">
        Homes
    </v-btn>
    <v-btn class="buttons" :to="'/live'">
        Live
    </v-btn>
    <v-btn class="buttons"> 
        <p> Analysis </p>
    </v-btn>
    <v-spacer></v-spacer>

  </v-app-bar>
</template>

<style>
.buttons {
    margin-right : 20px
}
</style> 