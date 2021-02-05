<template>
    <div class="recipe">
        <div id="title">{{ title }}</div>
        <div id="under-title">{{ date }}</div>
    </div>
</template>

<script>
export default {
    name: "recipe-item",
    props: ['title', 'date']
}
</script>

<style scoped>
    .recipe {
        border: 2px solid;
        border-radius: 5px;
        padding: 10px;
        margin: 0 5px 10px 5px;
    }

    #title {
        font-size: 24px;
        font-weight: bold;
    }

    #under-title {
        font-size: 12px;
        color:darkslategray;
        font-style: italic;
        margin: 2.5px 0 0 5px;
    }
</style>