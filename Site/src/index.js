import Vue from "vue"
import VueRouter from "vue-router"
import App from "./app.vue"
import routes from "./routes/routes"

Vue.use(VueRouter);
const router = new VueRouter({routes});

new Vue({
    router,
    render: (createEL) => createEL(App)
}).$mount("#app");

