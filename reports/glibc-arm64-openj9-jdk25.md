---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 09:10:47 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 8 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (4 unique values: 32-38 cores)</summary>

```
1795010743 33
1795010748 33
1795010753 33
1795010758 33
1795010763 33
1795010768 33
1795010773 33
1795010779 32
1795010784 32
1795010789 32
1795010794 32
1795010799 37
1795010804 37
1795010809 37
1795010814 37
1795010819 37
1795010824 37
1795010829 37
1795010834 37
1795010839 37
```
</details>

---

