/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:05:15 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/19 13:59:48 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MESSAGES_H
# define ERROR_MESSAGES_H

# define ERR_ARGS			"Wrong # of arguments: ./fdf map_file"
# define ERR_MAP			"Bad formatting of the map_file"
# define ERR_LINE_W			"Bad formatting of the map_file: wrong line length"
# define ERR_READING		"Cannot read the map_file"
# define ERR_FD_OPEN		"Could not open the map_file"
# define ERR_FD_CLOSE		"Could not close the map_file"
# define ERR_FD_IS_DIR		"The file is a directory, not a map"
# define ERR_MEM			"Memory allocation failed"

#endif
