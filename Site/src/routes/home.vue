<template>
    <div>
        <sensor-data/>
        <gallery/>
    </div>
    
</template>

<script>
import Store from "../stores/Store"

import sensorData from "../components/sensorData.vue"
import gallery from "../components/gallery.vue"

export default {
    name: "App",
    components: { gallery, sensorData },
    mounted() {
        Store.data.back = false;
    }
};
</script>
