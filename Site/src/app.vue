<template>
    <div>
        <div id="title">{{title}}</div>
        <sensor-data/>
    </div>
</template>

<script>
import sensorData from "./components/sensorData.vue"

export default {
    name: "App",
    components: {sensorData},
    data() {
        return {
            title: "My Sauna"
        }
    }
};
</script>

<style>
    @import url('https://fonts.googleapis.com/css2?family=Open+Sans:wght@400;600&display=swap');

    * {
        /* box-sizing: border-box; */
    }

    body {
        margin: 0;
        overflow-x: hidden;
        font-family: 'Open Sans', sans-serif;
    }
</style>

<style scoped>
    #title {
        font-weight: 600;
        text-align: center;
        font-size: 22px;
        padding: 24px 0 12px 0;
    }

    #wheel {
        background: conic-gradient(
            hsl(360, 100%, 50%),
            hsl(315, 100%, 50%),
            hsl(270, 100%, 50%),
            hsl(225, 100%, 50%),
            hsl(180, 100%, 50%),
            hsl(135, 100%, 50%),
            hsl(90, 100%, 50%),
            hsl(45, 100%, 50%),
            hsl(0, 100%, 50%)
        );
        height: 100px;
        width: 100px;
    }
</style>