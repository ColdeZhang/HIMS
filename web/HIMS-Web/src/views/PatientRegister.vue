<template>
    <n-space vertical>

        <h2>挂号</h2>

        <n-divider />

        <n-steps :current="(current_stage as number)" :status="currentStatus">
            <n-step title="查询信息" description="放置身份证至读卡器或手动输入身份证查询信息" />
            <n-step title="核验/登记" description="核验个人信息准确性 修改或补充有误处" />
            <n-step title="选择科室" description="在导诊人员的帮助下选择合适的挂号科室" />
            <n-step title="挂号缴费" description="缴纳挂号费 完成挂号 携带好证件前往科室就诊" />
        </n-steps>

        <n-divider />

        <n-form v-if="current_stage == 1" label-placement="top" label-align="left">
            <n-grid :cols="4" :x-gap="20">
                <n-form-item-gi span="3" label="身份证">
                    <n-input 
                        placeholder="请输入身份证号" 
                        v-model:value="current_patient.idn" 
                        clearable
                        maxlength="18"
                        show-count
                        :allow-input="verifyIDN"
                        @input="getPatientListByIdn" 
                    />
                </n-form-item-gi>

                <n-form-item-gi span="1">
                    <n-button type="primary" @click="chooseNoExistPatient" :disabled=isPatientExist>添加患者</n-button>
                </n-form-item-gi>

                <n-form-item-gi span="4">
                    <n-list bordered style="width: 90%">
                        <template #header>检索到相关信息：{{patients_list.length}} 条</template>
                        <template #footer>提示：如患者已在系统有记录 则从列表中选择 如果列表为空则需要添加患者信息</template>
                        <n-list-item v-for="i in patients_list">
                            <template #suffix>
                                <n-button dashed size="large" @click="chooseExistPatient(i)">选择</n-button>
                            </template>
                            <n-thing :title="((i as any).name)" :title-extra="(i as any).idn"></n-thing>
                        </n-list-item>
                    </n-list>
                </n-form-item-gi>
            </n-grid>
        </n-form>

        <n-form v-if="current_stage == 2" label-placement="top" label-align="left">

            <n-grid :cols="4" :x-gap="20">
                <n-form-item-gi span="4" label="身份证号:" :required="true">
                    <n-input 
                        placeholder="请输入身份证号" 
                        v-model:value="current_patient.idn" 
                        clearable
                        maxlength="18"
                        show-count
                        :allow-input="verifyIDN"
                    />
                </n-form-item-gi>

                <n-form-item-gi span="2" label="姓名:" :required="true">
                    <n-input v-model:value="current_patient.name" placeholder="" />
                </n-form-item-gi>

                <n-form-item-gi span="2" label="联系电话:" :required="true">
                    <n-input v-model:value="current_patient.phone" placeholder="" />
                </n-form-item-gi>

                <n-form-item-gi span="1" label="出生日期:" :required="true">
                    <n-date-picker v-model:value="current_patient.birth" type="date" />
                </n-form-item-gi>

                <n-form-item-gi span="1" label="性别:" :required="true">
                    <n-radio-group v-model:value="current_patient.gender" name="radiogroup">
                        <n-radio v-for="i in gender_group" :key="i.gender" :value="i.gender">
                            {{ i.label }}
                        </n-radio>
                    </n-radio-group>
                </n-form-item-gi>

                <n-form-item-gi span="1" label="民族:">
                    <n-input-group>
                        <n-select v-model:value="current_patient.ethnic" :options="ethnic_group" style="width: 100px" />
                        <n-input-group-label>族</n-input-group-label>
                    </n-input-group>
                </n-form-item-gi>

                <n-form-item-gi span="1" label="婚姻状况:">
                    <n-input v-model:value="current_patient.marital_status" placeholder="" />
                </n-form-item-gi>

                <n-form-item-gi span="4" label="户籍住址:">
                    <n-input v-model:value="current_patient.address" placeholder="" />
                </n-form-item-gi>

                <n-form-item-gi span="4" label="常住地址:" :required="true">
                    <n-input v-model:value="current_patient.address1" placeholder="" />
                </n-form-item-gi>

                <n-form-item-gi span="2" label="亲属电话:" :required="true">
                    <n-input v-model:value="current_patient.phone1" placeholder="" />
                </n-form-item-gi>

                <n-form-item-gi span="2" label="职业:">
                    <n-input v-model:value="current_patient.job" placeholder="" />
                </n-form-item-gi>

                <n-form-item-gi span="4" label="工作地址:">
                    <n-input v-model:value="current_patient.company" placeholder="" />
                </n-form-item-gi>

                <n-form-item-gi span="1">
                    <n-button type="primary" @click="stage2to1" ghost>重新查询 上一步</n-button>
                </n-form-item-gi>

                <n-form-item-gi span="1" offset="2">
                    <n-button type="primary" @click="stage2to3" ghost>确认无误 下一步</n-button>
                </n-form-item-gi>

            </n-grid>
        </n-form>

        <n-form v-if="current_stage == 3" label-placement="top" label-align="left">
            <n-grid :cols="4" :x-gap="20">
                <n-form-item-gi span="1">
                    <n-button type="primary" @click="prev" ghost>返回上一步</n-button>
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
    NFormItemGi,
    NInputGroup,
    NInputGroupLabel,
    NList,
    NListItem,
    NThing
} from "naive-ui";
import { 
    ref,
    onMounted,
    onBeforeMount
} from "vue";
import axios from "axios";
import type { StepsProps } from "naive-ui";
import { sleep } from "seemly";

// 创建数据结构
interface Patient {
    is_new: boolean;

    uuid: string;
    name: string;
    idn: string;
    birth: number;
    gender: number;
    ethnic: number;
    marital_status: string;
    job: string;
    company: string;
    address: string;
    address1: string;
    phone: string;
    phone1: string;
    create_time: string;
    update_time: string;
}

const ethnic_group = ref([]);
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

const current_patient=ref<Patient>({
    is_new: true,
    uuid: "",
    name: "",
    idn: "",
    birth: 0,
    gender: 0,
    ethnic: 1,
    marital_status: "",
    job: "",
    company: "",
    address: "",
    address1: "",
    phone: "",
    phone1: "",
    create_time: "",
    update_time: "",
})

// 所处步骤
const current_stage = ref<number | null>(1);

const notify = useNotification();
const currentStatus = ref<StepsProps["status"]>("process");

const isPatientExist = ref(true);

const patients_list = ref([]);

// 在创建页面之前
onBeforeMount(() => {
    // 加载民族信息
    axios
        .get("/static/ethnic", {})
        .then(function (response) {
            ethnic_group.value = response.data["ethnic_list"];
            console.log(ethnic_group.value);
        }).catch(function (error) {
            console.log(error);
            notifyNetError();
        })
});

// 身份证输入验证 只允许输入数字和x
function verifyIDN(value: string){
    const reg = /^[0-9x]+$/;
    return !value || reg.test(value);
}

// 下一页
function next () {
    if (current_stage.value === null) current_stage.value = 1
    else if (current_stage.value >= 4) current_stage.value = null
    else current_stage.value++
}
// 上一页
function prev () {
    if (current_stage.value === 0) current_stage.value = null
    else if (current_stage.value === null) current_stage.value = 4
    else current_stage.value--
}

// 根据身份证实时获取患者列表
function getPatientListByIdn() {
    if (current_patient.value.idn.length === 0){
        patients_list.value = [];
        isPatientExist.value = true;
        return;
    }
    else if(current_patient.value.idn.length >= 4 && current_patient.value.idn.length%4 === 0){
        axios
        .get("/patient/byIdn", {
            params: {
                idn: current_patient.value.idn,
            },
        })
        .then(function (response) {
            console.log(response);
            patients_list.value = response.data["result"];
            if (patients_list.value.length === 0) {
                isPatientExist.value = false;
            } else {
                isPatientExist.value = true;
            }
        })
        .catch(function (error) {
            console.log(error);
            notifyNetError();
        })
        .then(function () {
            // 总是会执行
        });
    }
}

// 提示网络错误
function notifyNetError() {
    notify.error({
        title: "连接失败",
        content: "获取系统后台数据失败，请检查网络连接。",
        duration: 3000,
    });
}

// 创建患者信息
function createPatient() {
    axios
        .post("/patient", {
            name: current_patient.value.name,
            idn: current_patient.value.idn,
            birth: current_patient.value.birth,
            gender: current_patient.value.gender,
            ethnic: current_patient.value.ethnic,
            marital_status: current_patient.value.marital_status,
            job: current_patient.value.job,
            company: current_patient.value.company,
            address: current_patient.value.address,
            address1: current_patient.value.address1,
            phone: current_patient.value.phone,
            phone1: current_patient.value.phone1,
        })
        .then(function (response) {
            console.log(response);
            if (response.data["code"] === 200) {
                notify.success({
                    title: "创建成功",
                    content: "患者信息创建成功。",
                    duration: 3000,
                });
                current_patient.value.uuid = response.data["uuid"];
                current_patient.value.is_new = false;
            } else {
                notify.error({
                    title: "创建失败",
                    content: "患者信息创建失败。",
                    duration: 3000,
                });
            }
        })
        .catch(function (error) {
            console.log(error);
            notifyNetError();
        })
}

// 第一步到第二步 选择已有患者
function chooseExistPatient(item: Patient) {
    current_patient.value = item;
    current_patient.value.is_new = false;
    next();
}

// 第一步到第二步 新建患者
function chooseNoExistPatient(){
    current_patient.value.is_new = true;
    next();
}

// 第二步到第三步跳转
function stage2to3(){
    if (current_patient.value.is_new){
        createPatient();
    }
    next();
}

// 第二步到第一步返回
function stage2to1(){
    current_patient.value.uuid = "";
    current_patient.value.name = "";
    current_patient.value.birth = 0;
    current_patient.value.gender = 0;
    current_patient.value.ethnic = 1;
    current_patient.value.marital_status = "";
    current_patient.value.job = "";
    current_patient.value.company = "";
    current_patient.value.address = "";
    current_patient.value.address1 = "";
    current_patient.value.phone = "";
    current_patient.value.phone1 = "";
    current_patient.value.create_time = "";
    current_patient.value.update_time = "";
    prev();
}
</script>
