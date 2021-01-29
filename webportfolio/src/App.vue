<template>
  <div class="flex flex-col m-0" id="app">
    <router-view/>
    <footer class="mt-auto p-2 flex justify-center text-white">
      This is a website developed as part of coursework at the University of the Highlands and Islands.
    </footer>
  </div>
</template>

<style scoped>
#app {
   height: 100vh;
}

</style>