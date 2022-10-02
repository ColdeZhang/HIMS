<template>
    <provider>
        <router-view></router-view>
    </provider>
</template>



<script setup lang="ts">
import { Provider } from './components';
import axios from 'axios';

axios.defaults.baseURL = 'http://127.0.0.1:8000/';

</script>