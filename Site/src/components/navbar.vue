<template>
    <nav>
        <div class="title"><h4>{{ siteName }}</h4></div>
        <ul class="nav-links">
            <li v-for="nav_item in nav_items" :key="nav_item"><a v-bind:href="'#' + _.lowerCase(nav_item)">{{ nav_item }}</a></li>
        </ul>
        <div class="burger" @click="navSlide">
            <div class="line1"></div>
            <div class="line2"></div>
            <div class="line3"></div>
        </div>
    </nav>
</template>

<script>
export default {
    name:"navbar",
    data() {
        return {
            siteName: "Haenen Recepten",

            nav_items: ["Recepten", "Kalender", "About", "Test"]
        }
    },
    methods: {
        navSlide: function() {
            const burger = document.querySelector(".burger");
            const nav = document.querySelector(".nav-links");
            const navLinks = document.querySelectorAll(".nav-links li");

            nav.classList.toggle("nav-active");
            burger.classList.toggle("toggle");

            navLinks.forEach((link, index) => {
                if(link.style.animation ) link.style.animation = '';
                else link.style.animation = `navLinkFade 0.5s ease forwards ${index / 7 + 0.3}s`;
            });
        }
    }
}
</script>

<style scoped>
    nav {
        display: flex;
        justify-content: center;
        align-items: center;
        min-height: 10vh;
        background-color: #774570;
        color: whitesmoke;
    }

    .title {
        text-transform: uppercase;
        letter-spacing: 4px;
        font-size: 15px;
        font-family: 'Raleway', sans-serif;
    }

    .nav-links {
        display: flex;
        flex-direction: column;
        width: 50%;
        position: absolute;
        right: 0px;
        height: 90vh;
        top: 10vh;
        background-color: inherit;
        margin: 0;
        padding-top: 2vh;
        align-items: center;
        justify-content: flex-start;
        transform: translateX(100%);
        transition: transform 0.5s ease-in;
    }

    .nav-links li {
        list-style: none;
        padding-bottom: 4vh;
        /* opacity: 0; */
    }

    .nav-links a {
        color: whitesmoke;
        text-decoration: none;
        letter-spacing: 1.5px;
        font-weight: bold;
        font-size: 14px;
    }

    .burger {
        position: absolute;
        right: 15px;
        cursor: pointer;
    }

    .burger div {
        width: 25px;
        height: 2px;
        border-radius: 1px;
        background-color: whitesmoke;
        margin: 5px;
        transition: all 0.3s ease;
    }

    @media only screen and (min-width: 500px) {
        .burger {
            right: 30px;
        }

        .title {
            font-size: 22px;
        }
        .nav-links {
            width: 40%;
        }
    }

    @media only screen and (min-width: 800px) {
        nav {
            justify-content: space-around;
        }

        .burger {
            display: none;
        }

        .nav-links {
            position: static;
            height: auto;
            margin: inherit;
            justify-content: space-around;
            flex-direction: row;
            width: 50%;
            padding-bottom: 0;
            transform: translateX(0%);
            transition: transform 0.5s ease-in;
        }

        .nav-links li {
            opacity: 1;
        }

        .nav-links a {
            font-size: 16px;
        }
    }

    @media only screen and (min-width: 1200px) {
        .nav-links {
            width: 40%;
        }
        
        .title {
            font-size: 26px;
        }        
    }

    @media only screen and (min-width: 1500px) {
        .nav-links {
            width: 30%;
        }

        .nav-links a {
            font-size: 19px;
        }
    }

    .nav-active {
        transform: translateX(0);
    }

    @keyframes navLinkFade {
        from {
            opacity: 0;
            transform: translateX(50px);
        }
        to {
            opacity: 1;
            transform: translateX(0);
        }
    }

    .toggle .line1 {
        transform: rotate(-45deg) translate(-4px, 5px);
    }

    .toggle .line2 {
        opacity: 0;
    }

    .toggle .line3 {
        transform: rotate(45deg) translate(-4.5px, -6px);
    }
</style>