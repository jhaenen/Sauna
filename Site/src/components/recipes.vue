<template>
    <div id="recipes" v-if="respAvailable">
        <div v-for="items in itemPairs" v-bind:key="items[0].id" class="row">
            <div v-bind:key="recipe.id" v-for="recipe in items" v-bind:class="{ 'col-12': (chunkSize == 1), 'col-6': (chunkSize == 2), 'col-4': (chunkSize == 3), 'col-3': (chunkSize == 4), 'col-2': (chunkSize == 6) }">
                <recipe v-bind:title="recipe.name" v-bind:date="formatDate(recipe.date)"/>
            </div>
        </div>
    </div>
</template>

<script>
import recipe from "./recipe_item.vue"

export default {
    name: "recipes",
    components: { recipe },
    props: ['chunkSize'],
    data() {
        return {
            recipes: [],
            respAvailable: false,
        };
    },
    created() {
        fetch("/recipe.json")
        .then(resp => resp.json())
        .then(data => {
            this.respAvailable = true;
            this.recipes = data;
        });
    },
    computed: {
        itemPairs() { return _.chunk(this.recipes, this.chunkSize); }
    },
    methods: {
        formatDate: function(dateString) {
            const date = new Date(dateString);
            return date.toLocaleDateString("nl-NL", { weekday: "short", year: "numeric", month: 'long', day: 'numeric' });
        }
    }
}
</script>

<style scoped>
    #recipes {
        margin: 10px;
    }
</style>