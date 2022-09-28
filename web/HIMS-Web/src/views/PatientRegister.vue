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
import { ref } from "vue";
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
const ethnic_group = ref([
    { value: 1, label: "汉" },
    { value: 2, label: "蒙古" },
    { value: 3, label: "回" },
    { value: 4, label: "藏" },
    { value: 5, label: "维吾尔" },
    { value: 6, label: "苗" },
    { value: 7, label: "彝" },
    { value: 8, label: "壮" },
    { value: 9, label: "布依" },
    { value: 10, label: "朝鲜" },
    { value: 11, label: "满" },
    { value: 12, label: "侗" },
    { value: 13, label: "瑶" },
    { value: 14, label: "白" },
    { value: 15, label: "土家" },
    { value: 16, label: "哈尼" },
    { value: 17, label: "哈萨克" },
    { value: 18, label: "傣" },
    { value: 19, label: "黎" },
    { value: 20, label: "傈僳" },
    { value: 21, label: "佤" },
    { value: 22, label: "畲" },
    { value: 23, label: "高山" },
    { value: 24, label: "拉祜" },
    { value: 25, label: "水" },
    { value: 26, label: "东乡" },
    { value: 27, label: "纳西" },
    { value: 28, label: "景颇" },
    { value: 29, label: "柯尔克孜" },
    { value: 30, label: "土" },
    { value: 31, label: "达翰尔" },
    { value: 32, label: "么佬" },
    { value: 33, label: "羌" },
    { value: 34, label: "布朗" },
    { value: 35, label: "撒拉" },
    { value: 36, label: "毛南" },
    { value: 37, label: "仡佬" },
    { value: 38, label: "锡伯" },
    { value: 39, label: "阿昌" },
    { value: 40, label: "普米" },
    { value: 41, label: "塔吉克" },
    { value: 42, label: "怒" },
    { value: 43, label: "乌孜别克" },
    { value: 44, label: "俄罗斯" },
    { value: 45, label: "鄂温克" },
    { value: 46, label: "德昂" },
    { value: 47, label: "保安" },
    { value: 48, label: "裕固" },
    { value: 49, label: "京" },
    { value: 50, label: "塔塔尔" },
    { value: 51, label: "独龙" },
    { value: 52, label: "鄂伦春" },
    { value: 53, label: "赫哲" },
    { value: 54, label: "门巴" },
    { value: 55, label: "珞巴" },
    { value: 56, label: "基诺" },
]);

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
</script>
