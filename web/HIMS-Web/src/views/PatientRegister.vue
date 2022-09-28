<template>
    <n-space vertical style="width: 150%;">

        <h2>挂号</h2>

        <n-divider />

        <n-steps :current="(currentRef as number)" :status="currentStatus">
            <n-step title="查询信息" description="放置身份证至读卡器或手动输入身份证查询信息" />
            <n-step title="核验/登记" description="核验个人信息准确性 修改或补充有误处" />
            <n-step title="选择科室" description="在导诊人员的帮助下选择合适的挂号科室" />
            <n-step title="挂号缴费" description="缴纳挂号费 完成挂号 携带好证件前往科室就诊" />
        </n-steps>

        <n-divider />

        <n-form label-placement="top" label-width="100" label-align="left">

            <n-grid :cols="4" :x-gap="20">
                <n-form-item-gi span="4" label="身份证号:" :required="true">
                    <n-input v-model:value="idn" placeholder="" />
                </n-form-item-gi>

                <n-form-item-gi span="2" label="姓名:" :required="true">
                    <n-input v-model:value="name" placeholder="" />
                </n-form-item-gi>

                <n-form-item-gi span="2" label="联系电话:" :required="true">
                    <n-input v-model:value="phone" placeholder="" />
                </n-form-item-gi>

                <n-form-item-gi span="1" label="出生日期:" :required="true">
                    <n-date-picker v-model:value="birth" type="date" />
                </n-form-item-gi>

                <n-form-item-gi span="1" label="性别:" :required="true">
                    <n-radio-group v-model:value="gender" name="radiogroup">
                        <n-radio v-for="i in gender_group" :key="i.gender" :value="i.gender">
                            {{ i.label }}
                        </n-radio>
                    </n-radio-group>
                </n-form-item-gi>

                <n-form-item-gi span="1" label="民族:">
                    <n-space justify="space-between">
                        <n-select v-model:value="ethnic" :options="ethnic_group" style="width: 100px" />
                        <p style="margin-top: 30%">族</p>
                    </n-space>
                </n-form-item-gi>

                <n-form-item-gi span="1" label="婚姻状况:">
                    <n-input v-model:value="marital_status" placeholder="" />
                </n-form-item-gi>

                <n-form-item-gi span="4" label="户籍住址:">
                    <n-input v-model:value="address" placeholder="" />
                </n-form-item-gi>

                <n-form-item-gi span="4" label="常住地址:" :required="true">
                    <n-input v-model:value="address1" placeholder="" />
                </n-form-item-gi>

                <n-form-item-gi span="2" label="亲属电话:" :required="true">
                    <n-input v-model:value="phone1" placeholder="" />
                </n-form-item-gi>

                <n-form-item-gi span="2" label="职业:">
                    <n-input v-model:value="job" placeholder="" />
                </n-form-item-gi>

                <n-form-item-gi span="4" label="工作地址:">
                    <n-input v-model:value="company" placeholder="" />
                </n-form-item-gi>

                <n-form-item-gi span="1" offset="1">
                    <n-button type="primary" @click="notifySuccess" ghost>挂号</n-button>
                </n-form-item-gi>

            </n-grid>
        </n-form>
    </n-space>
</template>

<script setup lang="ts">
import {
    NButton,
    NInput,
    NForm,
    NFormItem,
    NDatePicker,
    NRadio,
    NRadioGroup,
    NGrid,
    NGridItem,
    NSpace,
    NNotificationProvider,
    useNotification,
    NSelect,
    NStep,
    NSteps,
    NDivider,
    NFormItemGi
} from "naive-ui";
import { 
    ref,
    onMounted,
    onBeforeMount
} from "vue";
import axios from "axios";
import type { StepsProps } from "naive-ui";

const idn = ref("");
const name = ref("");
const birth = ref(0);
const gender = ref(1);
const gender_group = ref([
    {
        gender: 0,
        label: "女",
    },
    {
        gender: 1,
        label: "男",
    },
]);

const ethnic = ref(1);
const ethnic_group = ref([]);

const marital_status = ref("");
const job = ref("");
const company = ref("");
const address = ref("");
const address1 = ref("");
const phone = ref("");
const phone1 = ref("");
const create_time = ref("");
const update_time = ref("");

const currentRef = ref<number | null>(1);

const notify = useNotification();
const currentStatus = ref<StepsProps["status"]>("process");

function notifySuccess() {
    notify.success({
        title: "Success",
        content: ethnic.value + "挂号成功",
        duration: 3000,
    });

    axios
        .get("/patient/byUuid", {
            params: {
                uuid: "c402ed28-606e-4f5e-902a-4bde8ce840e9",
            },
        })
        .then(function (response) {
            console.log(response);
            name.value = response.data["result"]["name"];
        })
        .catch(function (error) {
            console.log(error);
        })
        .then(function () {
            // 总是会执行
        });
}

// 在创建页面之前加载数据
onBeforeMount(() => {
    axios
        .get("/static/ethnic", {})
        .then(function (response) {
            ethnic_group.value = response.data["ethnic_list"];
            console.log(ethnic_group.value);
        }).catch(function (error) {
            notify.error({
                title: "错误",
                content: "获取民族列表错误",
                duration: 3000,
            });
        })
});

</script>
