<template>
    <div id="titleBar">
        <div id="title">{{title}}</div>
        <dark-mode-icon id="dm" :class="{icon: true, clickable: true, darkMode: SD.darkMode}" @click="SD.darkMode = !(SD.darkMode)"/>
        <back-icon v-if="SD.back" id="back" :class="{icon: true, clickable: true, darkMode: SD.darkMode}" @click="$router.push('/')"/>
    </div>
</template>

<script>
import Store from "../stores/Store"

import darkModeIcon from "../assets/darkmode_icon.svg"
const backIcon = () => import("../assets/back.svg")

export default {
    name: "titleBar",
    props: ['title'],
    components: {darkModeIcon, backIcon},
    data() {
        return {
            SD: Store.data
        }
    }
}
</script>

<style lang="scss" scoped>
    #titleBar {
        position: relative;
        display: flex;
        align-items: center;
        justify-content: space-evenly;
        padding: 28px 0 28px 0;
        margin: 0 auto;
        max-width: 1200px;
    }

    #title {
        font-weight: 600;
        text-align: center;
        font-size: 22px;
    }

    #dm {
        position: absolute;
        right: 24px;
    }

    #back {
        position: absolute;
        left: 24px;
    }

    .icon {
        width: 24px;
        height: 24px;
    }

    .icon.darkMode {
        .black {
            fill: #ffffff;
        }

        g {
            fill: #16191C;
            path {
                fill: #ffffff;
            }
        }

    }
</style>