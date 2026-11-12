---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 13:08:08 EST

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 7 |
| Sample Rate | 0.12/sec |
| Health Score | 8% |
| Threads | 5 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (2 unique values: 79-96 cores)</summary>

```
1794506568 79
1794506573 79
1794506578 79
1794506583 79
1794506588 79
1794506593 79
1794506598 79
1794506603 79
1794506608 79
1794506613 79
1794506618 79
1794506623 79
1794506628 79
1794506633 79
1794506638 79
1794506643 79
1794506648 79
1794506653 79
1794506658 79
1794506663 96
```
</details>

---

