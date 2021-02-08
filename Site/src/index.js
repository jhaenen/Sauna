import Vue from "vue"
import VueRouter from "vue-router"
import routes from "./routes"

const homePath = routes[0].redirect;
var homeIdx = -1;
var error = false;


if(routes.length > 1) {
    for(var i = 1; i < routes.length; i++) {
        if(routes[i].path == homePath) { homeIdx = i; break; }
    }

    if(homeIdx == -1) error = true;
} else error = true;

if(!error) {
    Vue.use(VueRouter);
    const router = new VueRouter({routes});

    new Vue({
        router,
        render: (createEL) => createEL(routes[homeIdx].component)
    }).$mount("#app");
} else {
    console.error("No home directory found");
}

