<template>
  <v-app>
    <v-layout>
    <!-- <AppNavBar/> -->
    <v-navigation-drawer
        location="left"
        permanent
      >
        <template v-slot:prepend>
          <v-list-item
            lines="two"
            prepend-avatar="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcT97hU43u6vLrdfW4Vlrjd4HLzJvrehmCIa7g&usqp=CAU"
            subtitle="Active"
            title="Ry IOT Dashboard"
          ></v-list-item>
        </template>

        <v-divider></v-divider>

        <v-list density="compact" nav>
          
          <!-- <v-list-item class ="vsize" prepend-icon="mdi-home-city" title="Home" value="home" ></v-list-item> -->
          <v-spacer></v-spacer> 
          <v-list-item class ="vsize" prepend-icon="mdi-home-city" title="Dashboard" value="account" :to="'/live'"></v-list-item>
          <v-list-item  class = "vsize" prepend-icon="mdi-book-search-outline" title="Analysis" value="users" :to="'/nextpage'"></v-list-item>
        </v-list>
      </v-navigation-drawer>
      <!-- <v-main style="height: 250px"></v-main> -->
      <v-main>
     
     <router-view />
   </v-main>
    </v-layout>
   
  </v-app>
</template>

<script setup>

setInterval(() => {
  location.reload();
}, 30000);
  //
</script>

<style>
v-list-item {
  font-size: 10px; /* Adjust as needed */
}

.vsize {
  margin-top : 40px;
  font-size : 20px
}


</style>