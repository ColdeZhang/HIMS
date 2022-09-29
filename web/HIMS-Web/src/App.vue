<template>

    <n-config-provider :theme="lightTheme">
        <n-notification-provider>
            <n-config-provider :locale="zhCN" :date-locale="dateZhCN">
                <router-view></router-view>
            </n-config-provider>
        </n-notification-provider>
    </n-config-provider>

</template>



<script setup lang="ts">

import {
    NNotificationProvider,
    NConfigProvider,
    zhCN,
    dateZhCN,
    lightTheme
} from 'naive-ui'
import axios from 'axios';

axios.defaults.baseURL = 'http://127.0.0.1:8000/';

</script>