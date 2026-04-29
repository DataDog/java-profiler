---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-29 10:11:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 762 |
| Sample Rate | 12.70/sec |
| Health Score | 794% |
| Threads | 11 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (3 unique values: 67-87 cores)</summary>

```
1777471571 87
1777471576 87
1777471581 87
1777471586 72
1777471591 72
1777471596 72
1777471601 72
1777471606 72
1777471611 72
1777471616 72
1777471621 72
1777471626 72
1777471631 72
1777471636 72
1777471641 67
1777471646 67
1777471651 67
1777471656 67
1777471661 67
1777471666 67
```
</details>

---

