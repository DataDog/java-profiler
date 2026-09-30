---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 08:37:24 EDT

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 755 |
| Sample Rate | 12.58/sec |
| Health Score | 786% |
| Threads | 9 |
| Allocations | 327 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 808 |
| Sample Rate | 13.47/sec |
| Health Score | 842% |
| Threads | 10 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (3 unique values: 88-93 cores)</summary>

```
1790771592 90
1790771597 90
1790771603 90
1790771608 90
1790771613 90
1790771618 90
1790771623 90
1790771628 90
1790771633 90
1790771638 90
1790771643 90
1790771648 93
1790771653 93
1790771658 93
1790771663 93
1790771668 93
1790771673 93
1790771678 93
1790771683 93
1790771688 90
```
</details>

---

