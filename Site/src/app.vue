<template>
    <div id="content">
        <navbar />
        <recipes v-bind:chunkSize="chunkSize" />
    </div>
</template>

<script>
import recipes from "./components/recipes.vue"
import navbar from "./components/navbar.vue"

const mobileBreak = 800;
const laptopBreak = 1500;
const xlBreak = 2000;
const uwBreak = 3000;

export default {
    name: "App",
    components: { recipes, navbar },
    data() {
        return {
            chunkSize: 3
        };
    },
    mounted() {
        this.$nextTick(function() {
            window.addEventListener('resize', this.getWindowWidth);
            this.getWindowWidth();
        });
    },
    methods: {
        getWindowWidth(event) {
            if(document.documentElement.clientWidth <= mobileBreak) this.chunkSize = 1;
            else if(document.documentElement.clientWidth <= laptopBreak) this.chunkSize = 2;             
            else if(document.documentElement.clientWidth <= xlBreak) this.chunkSize = 3;
            else if(document.documentElement.clientWidth <= uwBreak) this.chunkSize = 4;
            else this.chunkSize = 6;
        }
    },
    beforeDestroy() {
        window.removeEventListener('resize', this.getWindowWidth);
    }
};
</script>

<style>
    * {
        box-sizing: border-box;
    }

    body {
        margin: 0;
        overflow-x: hidden;
    }

    #content {
        font-family: 'Montserrat', sans-serif;
    }

    .row::after {
        content: "";
        clear: both;
        display: table;
    }

    [class*="col-"] {
        float: left;
    }

    .col-1 {width: 8.33%;}
    .col-2 {width: 16.66%;}
    .col-3 {width: 25%;}
    .col-4 {width: 33.33%;}
    .col-5 {width: 41.66%;}
    .col-6 {width: 50%;}
    .col-7 {width: 58.33%;}
    .col-8 {width: 66.66%;}
    .col-9 {width: 75%;}
    .col-10 {width: 83.33%;}
    .col-11 {width: 91.66%;}
    .col-12 {width: 100%;}
</style>