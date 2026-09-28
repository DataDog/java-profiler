---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-28 08:01:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 12 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 211 |
| Sample Rate | 3.52/sec |
| Health Score | 220% |
| Threads | 12 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (2 unique values: 23-44 cores)</summary>

```
1790596654 23
1790596659 23
1790596664 23
1790596669 23
1790596674 23
1790596679 23
1790596684 23
1790596689 23
1790596694 23
1790596699 23
1790596705 23
1790596710 23
1790596715 23
1790596720 23
1790596725 23
1790596730 23
1790596735 23
1790596740 23
1790596745 23
1790596750 23
```
</details>

---

