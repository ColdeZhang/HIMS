import { createRouter, createWebHistory } from 'vue-router'
import Login from '../views/Login.vue'
import PatientRegister from '../views/PatientRegister.vue'

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/',
      name: 'home',
      component: Login
    },
    {
      path: '/login',
      name: 'login',
      component: Login
    },
    {
      path: '/patientRegister',
      name: 'Patient Register',
      component: PatientRegister
    }
  ]
})

export default router
