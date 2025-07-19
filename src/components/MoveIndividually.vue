


<template>
  <div class="motors">
      <MotorBlockBase  />

      <MotorBlockHombro />
      <MotorBlockCodo  />
  </div>
</template>

<script>
import { useMotorStore } from '@/stores/motorStore'
import MotorBlockBase from './MotorBlockBase.vue'
import MotorBlockCodo from './MotorBlockCodo.vue'
import MotorBlockHombro from './MotorBlockHombro.vue'

import DirectionButton from './DirectionButton.vue'
import AngleSteppingTrasmission from './AngleSteppingTrasmission.vue'
export default {
  name: 'MoveIndividually',
  components: {
    DirectionButton,
    AngleSteppingTrasmission,
    MotorBlockHombro,
    MotorBlockCodo,
    MotorBlockBase
  },
    data() {
    return {
      motorStore: useMotorStore(),
      // titulo: 'Componente MotorBlock',

    }
  },  
   props: {
    nombreMotor: {
      type: String,
      required: true
    },
    id: {
      type: String,
      required: true
    }
  },  
  methods: {
    // seleccionarDirreccion(id) {
    //   if (id === 'clockwise') {
    //     if(!this.clockwise){
    //       this.clockwise= true
    //       this.counterClockwise= false
    //     }
    //   } else {
    //     this.counterClockwise= !this.counterClockwise
    //     this.clockwise= !this.clockwise


    //   }
    // },
    // sumar(a, b) {
    //   return a + b;
    // }
  },  
computed: {
  motor1enable: {
      get() {
        return this.motorStore.motor1enable === 1
      },
      set(val) {
        this.motorStore.motor1enable = val ? 1 : 0
      }
    }
  }

}
</script>

<style scoped>
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