---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 05:58:34 EST

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 999 |
| Sample Rate | 16.65/sec |
| Health Score | 1041% |
| Threads | 12 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (3 unique values: 57-76 cores)</summary>

```
1793789563 57
1793789568 57
1793789573 76
1793789578 76
1793789583 76
1793789588 76
1793789593 76
1793789598 76
1793789603 76
1793789608 76
1793789613 76
1793789618 76
1793789623 76
1793789629 76
1793789634 76
1793789639 76
1793789644 76
1793789649 76
1793789654 59
1793789659 59
```
</details>

---

