import { defineStore } from 'pinia'

export const useMotorStore = defineStore('motor', {
  state: () => ({
    direction1: null,
    degrees1: 0,
    stepping1: 200,
    motor1enable: 0,
  }),

  getters: {
    motor1String(state) {
      return `${state.motor1enable}-${state.direction1}-${state.degrees1}-${state.stepping1}`
    }
  },

  actions: {
      setDirection(direction){
        console.log('clicking direction', direction)
        this.direction1 = direction
    }
  }
})