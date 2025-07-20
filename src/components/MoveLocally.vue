


<template>
  <div class="motors">
     <h3>direccion-angulo-microstepping</h3>
      <MotorBlockBase  />
      <MotorBlockHombro />
      <MotorBlockCodo  />
  </div>
    <button class="MoveIndividually-button" @click="handleEnviarlocal">Enviar</button>

</template>

<script>
import { useMotorStore } from '@/stores/motorStore'
import MotorBlockBase from './MotorBlockBase.vue'
import MotorBlockCodo from './MotorBlockCodo.vue'
import MotorBlockHombro from './MotorBlockHombro.vue'


export default {
  name: 'MoveIndividually',
  components: {
    MotorBlockBase,
    MotorBlockHombro,
    MotorBlockCodo,
  },
    data() {
    return {
      motorStore: useMotorStore(),


    }
  },  

  methods: {
    handleEnviarlocal() {
      const motorStore = useMotorStore()
      motorStore.enviarStringPositionlocal()
    },
  },  
computed: {

  }

}
</script>

<style scoped>
.MoveIndividually-button{
  margin-bottom: 3rem;
}
  .motors{
  display: flex;
justify-content: center;
align-items: center;
width: 100%;
padding-left: 1rem;
    flex-direction: column;

border: 2px solid green;
  }

  .direction-buttons{
    display: flex;
    justify-content: center;
    align-items: center;
    border: 1px solid grey;
    border-radius: 10px;
    flex-direction: column;
    width: 100%;

  }

  .motor-card {
  border: 1px solid gray;
  border-radius: 10px;
  /* background-color: green; */
}
</style>