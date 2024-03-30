import { defineStore } from "pinia";
import {ref , reactive} from 'vue'
import mqtt from 'mqtt'

export const useMqttStore = defineStore('mqtt_store', () => {

    const url = 'ws://broker.emqx.io:8083/mqtt'
    const client = ref(null);
    const newCardData = reactive({})

    const options = {
        clean: true,
      }

    function disconnect(){
        if(client.value!=null){
            client.value.end()
        }
    }

    function connect(){
        client.value  = mqtt.connect(url, options)
        client.value.on('connect', function () {
            console.log('Connected')
            // Subscribe to a topic
            client.value.subscribe('topic1', function (err) {
              if (!err) {
                // Publish a message to a topic
                client.value.publish('test', 'Hello mqtt')
              }
            })
          
          })

          client.value.on('disconnect', function () {
            console.log('disconnected')
          })
        
          client.value.on('message', function (topic, message) {
            // message is Buffer
            console.log(message.toString())
            if(topic=='topic1'){
                try{
                    newCardData.value = JSON.parse(message.toString())
                    console.log(newCardData.value.temperature)
                } catch (e){
                    console.log(e)
                }
                
            }
          })

    }

    return { connect , newCardData , disconnect}
  })