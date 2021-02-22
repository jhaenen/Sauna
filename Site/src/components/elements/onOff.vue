<template>
    <div class="container">
        <div :class="{bold: bold}">{{title}}</div>
        <div class="buttons">
            <div class="button on clickable bold" @click="on">AAN</div>
            <div class="button off clickable bold" @click="off">UIT</div>
        </div>
    </div>
</template>

<script>
import Store from "../../stores/Store"

export default {
    name: "onOff",
    props: ["title", "bold", "onLink", "offLink"],
    data() {
        return {
            SD: Store.data,
        }
    },
    methods: {
        on: function() {
            this.$emit("on");
            if(this.onLink != undefined) {
                var xhr = new XMLHttpRequest();   

                xhr.ontimeout = Store.methods.timeOutHandler;

                xhr.timeout = 5000;
                xhr.open("GET", this.onLink, true);  
                xhr.send(null);
            }
        },
        off: function() {
            this.$emit("off");
            if(this.offLink != undefined) {
                var xhr = new XMLHttpRequest();   

                xhr.ontimeout = Store.methods.timeOutHandler;

                xhr.timeout = 5000;
                xhr.open("GET", this.offLink, true);  
                xhr.send(null);
            }
        }
    }
}
</script>

<style>
    .container {
        width: 100%;
        padding: 20px 0;
        display: flex;
        justify-content: space-between;
        align-items: center;
        font-size: 18px;
    }

    .buttons {
        display: flex;
    }
    
    .button {
        width: 66px;
        height: 44px;
        line-height: 44px;
        text-align: center;
        vertical-align: middle;
        border-radius: 8px;
        -webkit-user-select: none;       
        -moz-user-select: none;
        -ms-user-select: none;
        user-select: none; 
        color: #ffffff;
    }

    .on {
        background: #5FA55A;
        margin-right: 8px;
    }

    .off {
        background: #FA5457;
    }
</style>