<template>
    <label id="container" class="clickable">
        <input type="checkbox" @click="$emit('toggle')">
        <span id="toggle" :class="{on: checked, bold: true}"><span id="txt">{{checked ? "AAN" : "UIT"}}</span><span id="handle"></span></span>
    </label>
</template>

<script>
export default {
    name: "toggleEl",
    props: ["checked"]
}
</script>

<style lang="scss" scoped>
    $w: 120px;
    $h: 48px;
    $handleSize: 28px;

    $onColor: #5FA55A;
    $offColor: #FA5457;

    #container {
        position: relative;
        width: $w;
        height: $h; 
    }

    input[type="checkbox"] {
        position: absolute;
        top: 0;
        left: 0;
        opacity: 0;
        width: 0;
        height: 0;
    }

    #toggle {
        position: absolute;
        top: 0;
        left: 0;
        width: 100%;
        height: 100%;
        border-radius: 24px;
        background: $offColor;
        color: white;
        font-size: 18px;

        #txt {
            position: absolute;
            top: 12px;
            right: 18px;
            user-select: none;
            transition: transform .5s;
        }

        #handle {
            position: absolute;
            background: white;
            border-radius: 50%;
            width: $handleSize;
            height: $handleSize;
            top: 10px;
            left: 10px;
            transition: transform .5s;
        }
    }

    #toggle.on {
        background: $onColor;

        #txt {
           transform: translateX(calc(100% + #{36px - $w}));
        }

        #handle {
            transform: translateX($w - $handleSize - 20);
        }
    }
</style>