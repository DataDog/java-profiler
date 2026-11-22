---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-22 15:55:18 EST

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 670 |
| Sample Rate | 11.17/sec |
| Health Score | 698% |
| Threads | 9 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (3 unique values: 28-57 cores)</summary>

```
1795380664 28
1795380669 28
1795380674 28
1795380679 28
1795380684 28
1795380689 28
1795380694 28
1795380699 28
1795380704 28
1795380709 28
1795380714 28
1795380719 28
1795380724 28
1795380729 48
1795380734 48
1795380739 48
1795380744 48
1795380749 57
1795380754 57
1795380759 57
```
</details>

---

