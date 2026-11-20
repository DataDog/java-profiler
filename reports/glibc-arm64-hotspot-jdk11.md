---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 04:30:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 126 |
| Sample Rate | 2.10/sec |
| Health Score | 131% |
| Threads | 11 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 11 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (3 unique values: 31-50 cores)</summary>

```
1795166806 50
1795166811 50
1795166816 45
1795166821 45
1795166826 45
1795166831 45
1795166836 45
1795166841 45
1795166846 45
1795166851 45
1795166856 45
1795166861 45
1795166866 45
1795166871 45
1795166876 45
1795166881 45
1795166886 45
1795166891 45
1795166896 45
1795166901 45
```
</details>

---

