---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ❌ FAIL

**Date:** 2026-11-16 05:57:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 84-84 cores)</summary>

```
1794826363 84
1794826368 84
1794826373 84
1794826378 84
1794826383 84
1794826388 84
1794826393 84
1794826399 84
1794826404 84
1794826409 84
1794826414 84
1794826419 84
1794826424 84
1794826429 84
1794826434 84
1794826439 84
1794826444 84
1794826449 84
1794826454 84
1794826459 84
```
</details>

---

