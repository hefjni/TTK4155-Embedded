#ifndef ADC_H_
#define ADC_H_

void ADC_init(void);

typedef enum {CHANNEL1, CHANNEL2, CHANNEL3, CHANNEL4} channel_t;

char ADC_get_data(void);

void ADC_start_read(channel_t channel);

void ADC_Test(void);



#endif /* ADC_H_ */