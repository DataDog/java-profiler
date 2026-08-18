---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-18 10:58:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 411 |
| Sample Rate | 6.85/sec |
| Health Score | 428% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (6 unique values: 21-32 cores)</summary>

```
1787064795 24
1787064800 24
1787064805 25
1787064810 25
1787064815 25
1787064820 25
1787064825 21
1787064830 21
1787064835 22
1787064840 22
1787064845 22
1787064850 25
1787064855 25
1787064860 25
1787064865 25
1787064870 30
1787064875 30
1787064880 30
1787064885 30
1787064890 30
```
</details>

---

