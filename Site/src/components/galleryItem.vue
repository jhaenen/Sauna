<template>
    <div class="galleryItem"><div class="item-text">{{itemText}}</div></div>
</template>

<script>
export default {
    name: "galleryItem",
    props: ["itemText"]
}
</script>

<style scoped>
    .galleryItem {
        position: relative;
        height: 60vh;
        width: min(80vw, calc((60vh * 230) / 307));
        /* background-image: url("../assets/sauna.png"); */
        background: brown;
        background-position: -100px -225px;
        border-radius: 8px;
        flex-shrink: 0;
    }

    .item-text {
        position: absolute;
        color: white;
        bottom: 18px;
        left: 24px;
        font-size: 36px;
        -webkit-user-select: none;       
        -moz-user-select: none;
        -ms-user-select: none;
        user-select: none; 
    }
</style>