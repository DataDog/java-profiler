---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 12:48:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (5 unique values: 82-89 cores)</summary>

```
1794505501 87
1794505506 87
1794505511 87
1794505516 87
1794505521 87
1794505526 87
1794505531 87
1794505536 89
1794505541 89
1794505546 89
1794505551 89
1794505556 89
1794505561 89
1794505566 89
1794505571 86
1794505576 86
1794505581 86
1794505586 86
1794505591 86
1794505596 86
```
</details>

---

