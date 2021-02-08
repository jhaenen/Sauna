<template>
    <router-link :to="itemLink" draggable="false" costum v-slot="{ href, navigate, isActive }">
        <NavLink class="clickable" :active="isActive" :href="href" @click="navigate">
            <div class="galleryItem" touch-action="none" :style="{backgroundImage: imgUrl}"><div class="item-text">{{itemText}}</div></div>
        </NavLink>
    </router-link>
</template>

<script>
export default {
    name: "galleryItem",
    props: ["itemText", "itemImg", "itemLink", "disable"],
    computed: {
        imgUrl: function () {
            return 'url("' + this.itemImg + '")';
        }
    }
}
</script>

<style scoped>
    .galleryItem {
        position: relative;
        height: 60vh;
        width: min(80vw, calc((60vh * 230) / 307));
        background-position: center right;
        background-size: auto 100%;
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