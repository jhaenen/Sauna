<template>
    <div>
        <div>{{hello}}</div>
    </div>
</template>

<script>
export default {
    name: "App",
    data() {
        return {
            hello: "Hello wouter!"
        }
    }
};
</script>

<style>
    @import url('https://fonts.googleapis.com/css2?family=Open+Sans:wght@400;600&display=swap');

    * {
        box-sizing: border-box;
    }

    body {
        margin: 0;
        overflow-x: hidden;
        font-family: 'Open Sans', sans-serif;
    }
</style>