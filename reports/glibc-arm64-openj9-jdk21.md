---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 13:41:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 11 |
| Allocations | 130 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 9 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (4 unique values: 25-43 cores)</summary>

```
1795199766 43
1795199771 43
1795199776 43
1795199781 43
1795199786 43
1795199791 42
1795199796 42
1795199801 42
1795199806 42
1795199811 42
1795199816 42
1795199821 42
1795199826 42
1795199831 40
1795199836 40
1795199841 40
1795199846 40
1795199851 25
1795199856 25
1795199861 25
```
</details>

---

