---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 09:10:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 11 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (3 unique values: 32-53 cores)</summary>

```
1795010733 32
1795010738 32
1795010743 32
1795010748 32
1795010753 32
1795010758 32
1795010764 32
1795010769 32
1795010774 32
1795010779 32
1795010784 32
1795010789 32
1795010794 32
1795010799 32
1795010804 32
1795010809 32
1795010814 32
1795010819 41
1795010824 41
1795010829 41
```
</details>

---

