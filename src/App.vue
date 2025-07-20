<script >

import MotorBlockBase from './components/MotorBlockBase.vue'
import MotorBlockHombro from './components/MotorBlockHombro.vue'
import MotorBlockCodo from './components/MotorBlockCodo.vue'
import MoveIndividually from './components/MoveLocally.vue'
import MoveGlobally from './components/MoveGlobally.vue'
import MoveToCoordinates from './components/MoveToCoordinates.vue'
import { useMotorStore } from './stores/motorStore'
// import { storeToRefs } from 'pinia'
export default {
  name: 'App',
  components: {

    MotorBlockBase,
    MotorBlockHombro,
    MotorBlockCodo,
    MoveIndividually,
    MoveGlobally,
    MoveToCoordinates
  },
    data() {
    return {
      selectedTab: '1',
      tabsNames: ['Mover localmente','Mover global','coordenadas']
    }
  },  
  methods: {
    handleEnviarlocal() {
      const motorStore = useMotorStore()
      motorStore.enviarStringPositionlocal()
    },
    seleccionarTab(tab){
      console.log('tab', tab)
      this.selectedTab = tab


    }
  }
}
</script>

<template>
  <header>
    <h1>Enviar al esp32 </h1>
    <div class="tabs">
      <button class="tab" @click="seleccionarTab('1')" >
        <p>Mover localmente</p>
      </button>      
      
      <button class="tab" @click="seleccionarTab('2')">
        <p>Mover global</p>
      </button>      

      <button class="tab" @click="seleccionarTab('3')">
        <p>dar coordenadas</p>
      </button>      

    </div>

    {{ tabsNames[parseInt(selectedTab-1)] }}
  </header>

  <main>
    <MoveIndividually v-if="this.selectedTab == '1'" />
    <MoveGlobally v-if="this.selectedTab == '2'" />
    <MoveToCoordinates v-if="this.selectedTab == '3'" />
  </main>
</template>

<style scoped>
.tabs{
  display: flex;

}
.tab{
  border: 2px solid gray;
  padding: 1rem;
}

.MoveIndividually-button{
  margin-bottom: 3rem;
}

h1 {
    color: #333;
    text-align: center;
}
header {
  line-height: 1.5;
  /* border: 2px solid red; */
  width: 100%;
  display: flex;
    justify-content: center;
  flex-direction: column;
  align-items: center;
  margin-bottom: 1rem;
}

.addMotorMovement{
  /* border: 2px solid red; */
  display: flex;
  justify-content: center;
  width: 100%;

}

.addMotorMovement button{
width: 10%;
height: 30px;
}

main {
  display: flex;
  justify-content: center;
  flex-direction: column;
  align-items: center;
  width: 100%;
}

</style>
