<template>
    <gallery/>
</template>

<script>
import Store from "../stores/Store"

import gallery from "../components/gallery.vue"

export default {
    name: "App",
    components: {gallery},
    mounted() {
        Store.data.back = false;
    }
};
</script>
