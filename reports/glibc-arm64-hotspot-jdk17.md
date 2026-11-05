---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-05 11:16:26 EST

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
| CPU Cores (start) | 19 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 189 |
| Sample Rate | 3.15/sec |
| Health Score | 197% |
| Threads | 11 |
| Allocations | 123 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 12 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (2 unique values: 19-21 cores)</summary>

```
1793895022 19
1793895027 19
1793895032 19
1793895037 19
1793895043 19
1793895048 19
1793895053 19
1793895058 19
1793895063 19
1793895068 19
1793895073 19
1793895078 19
1793895083 19
1793895088 19
1793895093 19
1793895098 19
1793895103 19
1793895108 19
1793895113 21
1793895118 21
```
</details>

---

