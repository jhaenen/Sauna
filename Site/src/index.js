import Vue from "vue"
import App from "./app.vue"

new Vue({
    render: (createEL) => createEL(App)
}).$mount("#app");