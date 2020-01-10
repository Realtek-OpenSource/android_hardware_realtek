#ifndef _RTK_UCTRL_WRAPPER_H_
#define _RTK_UCTRL_WRAPPER_H_

#include "rtk_uctrl.h"

struct reset_control;
struct clk;

struct uctrl * uctrl_get(const char *id);
void uctrl_put(struct uctrl *uctrl);
int uctrl_set(struct uctrl *uctrl);
int uctrl_clear(struct uctrl *uctrl);
int uctrl_state(struct uctrl *uctrl);

static inline struct clk * clk_get(void * unused_ptr __unused, const char *id)
{
    return (struct clk *)uctrl_get(id);
}

static inline void clk_put(struct clk *clk)
{
    uctrl_put((struct uctrl *)clk);
}

static inline int clk_enable(struct clk *clk)
{
    return uctrl_set((struct uctrl *)clk);
}

static inline void clk_disable(struct clk *clk)
{
    uctrl_clear((struct uctrl *)clk);    
}

static inline int __clk_is_enabled(struct clk *clk)
{
    return uctrl_state((struct uctrl *)clk);
}

static inline struct reset_control *reset_control_get(void * unused_ptr __unused, const char *id)
{
    return (struct reset_control *)uctrl_get(id);
}

static inline void reset_control_put(struct reset_control *rstc)
{
    uctrl_put((struct uctrl *)rstc);
}

static inline int reset_control_deassert(struct reset_control *rstc)
{
    return uctrl_set((struct uctrl *)rstc);    
}

static inline int reset_control_assert(struct reset_control *rstc)
{
    return uctrl_clear((struct uctrl *)rstc);
}

static inline int reset_control_reset(struct reset_control *rstc)
{
    int ret;
    ret = reset_control_assert(rstc);
    if (ret)
        return ret;

    return reset_control_deassert(rstc);
}

static inline int reset_control_status(struct reset_control *rstc)
{
    return uctrl_state((struct uctrl *)rstc);
}

#endif /* _RTK_UCTRL_WRAPPER_H_ */
