---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-19 00:58:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 8 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 842 |
| Sample Rate | 14.03/sec |
| Health Score | 877% |
| Threads | 10 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (2 unique values: 48-72 cores)</summary>

```
1789793647 48
1789793652 48
1789793657 48
1789793662 48
1789793667 48
1789793672 48
1789793677 48
1789793682 48
1789793687 48
1789793692 48
1789793697 48
1789793702 48
1789793707 48
1789793712 48
1789793717 48
1789793723 48
1789793728 48
1789793733 48
1789793738 48
1789793743 72
```
</details>

---

