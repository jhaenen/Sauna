import Home from "./home.vue"

export default [
    {
        path: '/', 
        redirect: '/home'
    },
    {
        path: '/home',
        component: Home
    }
];