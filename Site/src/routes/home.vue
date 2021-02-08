<template>
    <div id="body" :class="{lightMode: !(SD.darkMode), darkMode: SD.darkMode}">
        <title-bar :title="title" back="false"/>
        <sensor-data/>
        <gallery/>
    </div>
</template>

<script>
import Store from "../stores/Store"

import titleBar from "../components/titleBar.vue"
import sensorData from "../components/sensorData.vue"
import gallery from "../components/gallery.vue"

export default {
    name: "App",
    components: {sensorData, gallery, titleBar},

    data() {
        return {
            title: "Mijn sauna",
            SD: Store.data
        }
    }
};
</script>

<style>
    @import url("../site.css");
</style>
