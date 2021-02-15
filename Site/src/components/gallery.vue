<template>
    <div :class="{center: !overflow}">
        <div id="gallery">
            <gallery-item v-for="(item, index) in galleryItems" :key="index" :itemText="item.text" :itemImg="item.img" :itemLink="item.link"/>
            <div class="spacer">&nbsp;</div>
        </div>
    </div>
</template>

<script>
import galleryItem from "./galleryItem.vue"

export default {
    name: "gallery",
    components: {galleryItem},
    data() {
        return {
            overflow: false,
            galleryItems: [
                {text: "Sauna", img: "http://sauna.haenenweb.nl/assets/sauna_heater.jpg", link: "/sauna"},
                {text: "Verlichting", img: "http://sauna.haenenweb.nl/assets/sauna_verlichting.jpg", link: "/lights"}
            ]
        }
    },
    mounted() {
        var dragPerm = false;
        var hitPoint = 0;
        var diff = 0;
        var setPoint = 0;
        const gallery = document.getElementById("gallery");
        var setTarget = 0; 
        var curPoint = 0;
        var numTargets = gallery.childElementCount - 1;
        var paddingOffset = gallery.children[0].offsetLeft;
        var flick = false;
        var animate = false;
        var dragged = false;
        var link = "";

        this.overflow = gallery.scrollWidth > gallery.clientWidth;

        setInterval(() => {
            if(animate) {
                var dir = 0;
                if(curPoint < setPoint) { curPoint += 10; dir = 1; }
                else if(curPoint > setPoint) { curPoint -= 10; dir = -1; }

                gallery.scrollLeft = curPoint;

                if(dir == 1 && curPoint >= setPoint) { gallery.scrollLeft = setPoint; animate = false; }
                else if(dir == -1 && curPoint <= setPoint) { gallery.scrollLeft = setPoint; animate = false; }
            }
        }, 10);

        window.addEventListener("resize", () => {
            paddingOffset = gallery.children[0].offsetLeft;
            gallery.scrollLeft = gallery.children[setTarget].offsetLeft - paddingOffset;
            setPoint = gallery.children[setTarget].offsetLeft - paddingOffset;
            this.overflow = gallery.scrollWidth > gallery.clientWidth;
        });

        document.addEventListener("pointerdown", (e) => {
            if(e.target.className == "galleryItem" && e.buttons == 1) {
                if(this.overflow) {
                    dragPerm = true;
                    hitPoint = e.clientX;
                    animate = false;
                }

                link = e.target.attributes.data.value;
            }
        });

        document.addEventListener("pointerup", (e) => {
            if(dragPerm && this.overflow) {
                if(diff >= (paddingOffset + (gallery.children[setTarget].offsetWidth * .2))) {
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
                curPoint = gallery.scrollLeft;
                animate = true;
                setPoint = gallery.children[setTarget].offsetLeft - paddingOffset;
            }
            dragPerm = false;

            link = "";
            dragged = false;
        });

        document.addEventListener("pointermove", (e) => {
            if(e.buttons == 1 && dragPerm && this.overflow) {
                e.preventDefault();
                var tempDiff = hitPoint - e.clientX;
                if(Math.abs(diff) > 5) dragged = true;
                if(Math.abs(diff - tempDiff) > 25) flick = true;
                diff = tempDiff;
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
    $gap: 20px;

    #gallery {
        overflow: hidden;
        display: flex;
        align-items: center;
        margin-top: 28px;
        padding-left: 3vw;
    }

    #gallery::-webkit-scrollbar {
        display: none;
    }

    .spacer {
        width: 3vw;
        flex-shrink: 0;
    }

    #gallery > :not(:last-child)  {
        display: inline-flex;
        margin-right: $gap;
    }

    #gallery > :nth-last-child(2) {
        margin-right: 0;
    }
</style>