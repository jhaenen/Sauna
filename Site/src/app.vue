<template>
    <div id="body" :class="{lightMode: !(SD.darkMode), darkMode: SD.darkMode}">
        <title-bar :title="title" back="false"/>
        <sensor-data/>
        <router-view/>
    </div>
</template>

<script>
import Store from "./stores/Store"

import titleBar from "./components/titleBar.vue"
import sensorData from "./components/sensorData.vue"

export default {
    name: "App",
    components: {sensorData, titleBar},

    data() {
        return {
            title: "Mijn sauna",
            SD: Store.data
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

    .lightMode {
        color: #16191C;
        background: #FFFFFF;
    }

    .darkMode {
        background: #16191C;
        color: #FFFFFF;
    }

    #body {
        height: 100vh;
    }

    .clickable {
        cursor: pointer;
    }

    .bold {
        font-weight: 600;
    }
</style>
