---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-07 12:54:31 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 780 |
| Sample Rate | 13.00/sec |
| Health Score | 812% |
| Threads | 11 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (4 unique values: 70-92 cores)</summary>

```
1775580598 72
1775580603 70
1775580608 70
1775580613 70
1775580618 70
1775580623 70
1775580628 70
1775580633 72
1775580638 72
1775580643 72
1775580648 72
1775580653 92
1775580658 92
1775580663 92
1775580668 92
1775580673 92
1775580678 92
1775580683 92
1775580688 92
1775580693 92
```
</details>

---

