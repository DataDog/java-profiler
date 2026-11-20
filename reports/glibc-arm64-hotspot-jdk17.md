---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 13:41:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 12 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795199751 50
1795199756 50
1795199761 50
1795199766 50
1795199771 50
1795199776 50
1795199781 50
1795199786 50
1795199791 50
1795199796 50
1795199801 50
1795199806 50
1795199811 50
1795199816 50
1795199821 50
1795199826 50
1795199831 50
1795199836 50
1795199841 50
1795199846 50
```
</details>

---

