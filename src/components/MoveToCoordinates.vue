


<template>
   <!-- aqui poner cinematica inversa ir al punto en linea recta -->
    <button class="MoveGlobally-button" @click="handleEnviarCoordenadas">Enviar</button>

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

    }
  },  

  methods: {
    handleEnviarGlobal() {
      const motorStore = useMotorStore()
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