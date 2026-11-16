---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 10:44:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 8 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 9 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (4 unique values: 90-96 cores)</summary>

```
1794843613 96
1794843618 96
1794843623 96
1794843628 96
1794843633 96
1794843638 96
1794843643 96
1794843648 96
1794843653 96
1794843658 94
1794843663 94
1794843668 94
1794843673 94
1794843678 94
1794843683 94
1794843688 94
1794843693 94
1794843698 94
1794843703 92
1794843708 92
```
</details>

---

