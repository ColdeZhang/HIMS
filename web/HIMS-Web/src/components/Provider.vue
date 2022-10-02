<template>
  <n-config-provider :theme="theme">
    <n-global-style />
    <n-loading-bar-provider>
      <n-message-provider>
        <n-dialog-provider>
          <n-notification-provider>
            <slot />
            
          </n-notification-provider>
        </n-dialog-provider>
      </n-message-provider>
    </n-loading-bar-provider>
  </n-config-provider>
</template>
  
<script lang="ts" setup>
import { computed } from 'vue'
import { useOsTheme, darkTheme } from 'naive-ui'

const osTheme = useOsTheme()

// 深色模式
// const theme = computed(() => (osTheme.value === 'dark' ? darkTheme : null))
const theme = null

</script>
  