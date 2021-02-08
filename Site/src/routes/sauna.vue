<template>
    <div>Sauna</div>
</template>

<script>
import Store from "../stores/Store"

export default {
    name: "Sauna",
    mounted() {
        Store.data.back = true;
    }
};
</script>