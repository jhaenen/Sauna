import Home from "./home.vue"
const Sauna = () => import("./sauna.vue")
const Lights = () => import("./lights.vue")

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