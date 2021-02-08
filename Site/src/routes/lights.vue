<template>
    <div>Verlichting</div>
</template>

<script>
import Store from "../stores/Store"

export default {
    name: "Lights",
    mounted() {
        Store.data.back = true;
    }
};
</script>