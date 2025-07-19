


<template>
  <div >
      <div class="direction-buttons">
        <div class="motor-enable">


          <h2>Motor 1</h2>
          <input type="checkbox" v-model="motor1enable" />
           <p>motor1enable: {{ motor1enable }}</p>
        </div>
        <DirectionButton/>
        <AngleSteppingTrasmission/>
        </div>
        <!-- {{ clockwise }}
        {{ counterClockwise }} -->
         <h2>{{ motorStore.motor1String }}</h2>
  </div>
</template>

<script>
import { useMotorStore } from '@/stores/motorStore'

import DirectionButton from './DirectionButton.vue'
import AngleSteppingTrasmission from './AngleSteppingTrasmission.vue'
export default {
  name: 'MotorBlock',
  components: {
    DirectionButton,
    AngleSteppingTrasmission
  },
    data() {
    return {
      motorStore: useMotorStore(),
      // titulo: 'Componente MotorBlock',

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
  .motor-enable{
  display: flex;
justify-content: flex-start;
width: 100%;
padding-left: 1rem;
  }

  .direction-buttons{
    display: flex;
    justify-content: center;
    align-items: center;
    border: 2px solid red;
    flex-direction: column;
  }
</style>