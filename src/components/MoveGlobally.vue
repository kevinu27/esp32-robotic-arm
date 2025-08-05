


<template>
  <div class="motors">

     <h3>angulo motor base</h3>
     <input type="number" v-model.number="degrees1" />
     <h3>angulo motor hombro</h3>
     <input type="number" v-model.number="degrees2" />
     <h3>angulo motor codo</h3>
     <input type="number" v-model.number="degrees3" />
    {{ stringAngulosGlobal }}

  </div>
    <button class="MoveGlobally-button" @click="handleEnviarGlobal">Enviar</button>

</template>

<script>
import { useMotorStore } from '@/stores/motorStore'

export default {
  name: 'MoveGlobally',
  components: {

  },
    data() {
    return {
      motorStore: useMotorStore(),
      degrees1: 500,
      degrees2: 500,
      degrees3: 500,
    }
  },  

  methods: {
    handleEnviarGlobal() {
      const motorStore = useMotorStore()
      console.log('this.stringAngulosGlobal', this.stringAngulosGlobal)
      motorStore.enviarStringPositionGlobal(this.stringAngulosGlobal)
    },
  },

computed: {
    stringAngulosGlobal:{
          get() {
          return `${this.degrees1}/${this.degrees2}/${this.degrees3}`;
        },
    }
  }

}
</script>

<style scoped>
.MoveGlobally-button{
  margin-bottom: 3rem;
}

.motors{
  display: flex;
  flex-direction: column;
}

</style>