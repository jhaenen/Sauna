<template>
    <div id="gallery">
        <gallery-item itemText="Sauna"/>
        <gallery-item itemText="Verlichting"/>
        <div class="spacer">&nbsp;</div>
    </div>
</template>

<script>
import galleryItem from "./galleryItem.vue"

export default {
    name: "gallery",
    components: {galleryItem},
    data() {
        return {
            //dragPerm: false
        }
    },
    mounted() {
        var dragPerm = false;
        var hitPoint = 0;
        var diff = 0;
        var setPoint = 0;
        const gallery = document.getElementById("gallery");
        var setTarget = 0; 
        var numTargets = gallery.childElementCount - 1;
        var paddingOffset = gallery.children[0].offsetLeft;
        var flick = false;

        document.addEventListener("pointerdown", (e) => {
            if(e.target.className == "galleryItem") {
                dragPerm = true;
                hitPoint = e.clientX;
            }
        });

        document.addEventListener("pointerup", (e) => {
            if(dragPerm) {
                if(diff >= (paddingOffset + (gallery.children[setTarget].offsetWidth / 2))) {
                    if(setTarget >= (numTargets - 1)) setTarget = numTargets - 1;
                    else setTarget++;
                } else if((-diff) >= (paddingOffset + (gallery.children[setTarget].offsetWidth / 2))) {
                    if(setTarget <= 0) setTarget = 0;
                    else setTarget--;
                } else if(flick) {
                    if(setTarget >= numTargets) setTarget = numTargets - 1;
                    else if(setTarget < 0) setTarget = 0;
                    else if(diff > 0) setTarget++;
                    else if(setTarget > 0) setTarget--;
                }

                flick = false;

                diff = 0;
                gallery.scrollLeft = gallery.children[setTarget].offsetLeft - paddingOffset;
                setPoint = gallery.children[setTarget].offsetLeft - paddingOffset;
            }
            dragPerm = false;
        });

        document.addEventListener("pointermove", (e) => {
            if(e.buttons == 1 && dragPerm) {
                var tempDiff = hitPoint - e.clientX;
                if(Math.abs(diff - tempDiff) > 25) flick = true;
                diff = tempDiff;
                //console.log(diff)
                gallery.scrollLeft = setPoint + diff;
            }
        });
    }
}
</script>

<style lang="scss" scoped>
    $aspect: (60vh * 230) / 307;
    $clampWidth: 80vw;
    $padding: 50vw;

    #gallery {
        overflow: hidden;
        display: flex;
        align-items: center;
        justify-content: space-between;
        margin-top: 10vh;
        padding-left: calc(#{$padding} - (min(#{$clampWidth}, #{$aspect}) / 2));
    }

    #gallery::-webkit-scrollbar {
        display: none;
    }

    .spacer {
        width: 5vw;
        flex-shrink: 0;
    }

    #gallery > :not(:last-child)  {
        display: inline-flex;
        margin-right: calc(#{$padding - 5} - (min(#{$clampWidth}, #{$aspect}) / 2));
    }
</style>