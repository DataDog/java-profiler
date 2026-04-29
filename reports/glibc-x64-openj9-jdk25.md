---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-29 10:11:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 399 |
| Sample Rate | 6.65/sec |
| Health Score | 416% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 10 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (4 unique values: 65-74 cores)</summary>

```
1777471551 65
1777471556 65
1777471561 65
1777471566 65
1777471571 70
1777471576 70
1777471581 70
1777471586 70
1777471591 70
1777471596 68
1777471601 68
1777471606 68
1777471611 68
1777471616 68
1777471621 68
1777471626 68
1777471631 68
1777471636 68
1777471641 74
1777471646 74
```
</details>

---

