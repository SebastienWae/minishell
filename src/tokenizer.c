/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:44:15 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/03 14:47:26 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

static t_token_trans_matrix_row	token_trans_matrix[] = {
    // CURR STATE  // EVENT           // NEXT STATE
    { ST_INIT,     EV_ANY,               ST_IDLE    },
    { ST_IDLE,     EV_BUTTON_PUSHED,     ST_LED_ON  },
    { ST_LED_ON,   EV_TIME_OUT,          ST_LED_OFF },
    { ST_LED_ON,   EV_BUTTON_PUSHED,     ST_IDLE    },
    { ST_LED_OFF,  EV_TIME_OUT,          ST_LED_ON  },
    { ST_LED_OFF,  EV_BUTTON_PUSHED,     ST_IDLE    }
};

static t_token_handler	token_handlers[] = {
	// NAME         // FUNC
	{ "ST_INIT",      &Led_Init },      // ST_INIT
	{ "ST_IDLE",      &Led_Idle },      // ST_IDLE
	{ "ST_LED_ON",    &Led_On },        // ST_LED_ON
	{ "ST_LED_OFF",   &Led_Off },       // ST_LED_OFF
};
