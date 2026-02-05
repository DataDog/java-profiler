---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-04 19:34:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 11 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 788 |
| Sample Rate | 13.13/sec |
| Health Score | 821% |
| Threads | 12 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (2 unique values: 70-75 cores)</summary>

```
1770251363 75
1770251368 75
1770251373 75
1770251378 75
1770251383 70
1770251388 70
1770251393 70
1770251398 70
1770251403 70
1770251408 70
1770251413 70
1770251418 70
1770251423 70
1770251428 70
1770251433 70
1770251438 70
1770251443 70
1770251448 70
1770251453 70
1770251458 70
```
</details>

---

