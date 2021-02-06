<template>
    <div id="titleBar"><div id="title">{{title}}</div><dark-mode-icon :class="{icon: true, clickable: true, darkMode: SD.darkMode}" @click="SD.darkMode = !(SD.darkMode)"/></div>
    
</template>

<script>
import Store from "../stores/Store"

import darkModeIcon from "../assets/darkmode.svg"

export default {
    name: "titleBar",
    props: ['title', 'back'],
    components: {darkModeIcon},
    data() {
        return {
            SD: Store.data
        }
    }
}
</script>

<style scoped>
    #titleBar {
        position: relative;
        display: flex;
        align-items: center;
        justify-content: space-evenly;
        padding: 24px 0 30px 0;
    }

    #title {
        font-weight: 600;
        text-align: center;
        font-size: 22px;
    }

    .icon {
        position: absolute;
        width: 24px;
        height: 24px;
        right: 24px;
    }

    .icon.darkMode > .black {
        stroke: #ffffff;
        fill: #ffffff;
    }

    .icon.darkMode > .white {
        stroke: #ffffff;
        fill: #16191C;
    }
</style>