import Home from "./home.vue"
import Sauna from "./sauna.vue"
import Lights from "./lights.vue"

export default [
    {
        path: '/', 
        redirect: '/home'
    },
    {
        path: '/home',
        component: Home
    },
    {
        path: "/sauna",
        component: Sauna
    },
    {
        path: "/lights",
        component: Lights
    }
];