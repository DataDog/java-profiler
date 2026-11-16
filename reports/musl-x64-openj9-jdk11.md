---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 09:19:46 EST

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 619 |
| Sample Rate | 10.32/sec |
| Health Score | 645% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 836 |
| Sample Rate | 13.93/sec |
| Health Score | 871% |
| Threads | 10 |
| Allocations | 562 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1794838415 79
1794838420 79
1794838425 79
1794838430 79
1794838436 79
1794838441 79
1794838446 79
1794838451 81
1794838456 81
1794838461 81
1794838466 81
1794838471 81
1794838476 81
1794838481 81
1794838486 81
1794838491 81
1794838496 81
1794838501 81
1794838506 81
1794838511 81
```
</details>

---

