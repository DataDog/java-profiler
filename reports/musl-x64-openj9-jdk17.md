---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-01-29 09:48:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 18.80/sec |
| Health Score | 1175% |
| Threads | 10 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1113 |
| Sample Rate | 37.10/sec |
| Health Score | 2319% |
| Threads | 11 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (3 unique values: 55-61 cores)</summary>

```
1769697769 61
1769697774 61
1769697779 61
1769697784 61
1769697789 61
1769697794 61
1769697799 61
1769697804 59
1769697809 59
1769697814 59
1769697819 59
1769697824 59
1769697829 59
1769697834 59
1769697839 59
1769697844 59
1769697849 59
1769697854 59
1769697859 59
1769697864 59
```
</details>

---

