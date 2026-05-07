---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-07 13:16:14 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 11 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 160 |
| Sample Rate | 2.67/sec |
| Health Score | 167% |
| Threads | 15 |
| Allocations | 84 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1778173724 59
1778173729 59
1778173734 59
1778173739 59
1778173744 59
1778173749 59
1778173754 59
1778173759 59
1778173764 59
1778173769 59
1778173774 59
1778173779 59
1778173784 59
1778173789 59
1778173794 59
1778173799 64
1778173804 64
1778173809 64
1778173814 64
1778173819 64
```
</details>

---

