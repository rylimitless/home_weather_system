/**
 * main.js
 *
 * Bootstraps Vuetify and other plugins then mounts the App`
 */

// Plugins
import { registerPlugins } from '@/plugins'
import { OhVueIcon, addIcons } from "oh-vue-icons";
import { FaFlag, RiZhihuFill } from "oh-vue-icons/icons";

// Components
import App from './App.vue'

// Composables
import { createApp } from 'vue'

addIcons(FaFlag, RiZhihuFill);
const app = createApp(App)
app.component("v-icon", OhVueIcon);

registerPlugins(app)

app.mount('#app')
