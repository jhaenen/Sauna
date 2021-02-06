<template>
    <div id="body">
        <div id="title">{{title}}</div>
        <sensor-data/>
        <gallery/>
    </div>
</template>

<script>
import sensorData from "./components/sensorData.vue"
import gallery from "./components/gallery.vue"

export default {
    name: "App",
    components: {sensorData, gallery},
    data() {
        return {
            title: "My Sauna"
        }
    }
};
</script>

<style>
    @import url('https://fonts.googleapis.com/css2?family=Open+Sans:wght@400;600&display=swap');

    body {
        margin: 0;
        overflow-x: hidden;
        font-family: 'Open Sans', sans-serif;
        color: #16191C;
    }

    #body {
        height: 100vh;
    }
</style>

<style scoped>
    #title {
        font-weight: 600;
        text-align: center;
        font-size: 22px;
        padding: 24px 0 24px 0;
    }
</style>