<template >

    <n-form>
        <n-form-item>
            <h2>登录</h2>
        </n-form-item>
        <n-form-item label="用户名">
            <n-input 
                v-model:value="username" 
                placeholder=""
            />
        </n-form-item>
        <n-form-item label="密码">
            <n-input 
                v-model:value="password" 
                type="password" 
                show-password-on="click"
                placeholder=""
            />
        </n-form-item>
        <n-form-item>
            <n-button type="primary" @click="login" ghost>登录</n-button>
        </n-form-item>
    </n-form>

</template>


<script setup lang="ts">

import { NButton, NInput, NForm, NFormItem } from 'naive-ui'

import { ref } from 'vue'

const username = ref('')
const password = ref('')

function login() {
    console.log(username.value, password.value)
}

</script>