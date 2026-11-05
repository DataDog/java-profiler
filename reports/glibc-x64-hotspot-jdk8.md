---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-05 11:16:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 179 |
| Sample Rate | 2.98/sec |
| Health Score | 186% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 263 |
| Sample Rate | 4.38/sec |
| Health Score | 274% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 78-80 cores)</summary>

```
1793895008 80
1793895013 80
1793895018 80
1793895023 80
1793895028 80
1793895033 80
1793895038 80
1793895043 80
1793895048 80
1793895053 80
1793895058 80
1793895063 80
1793895068 80
1793895073 80
1793895078 80
1793895083 80
1793895088 80
1793895093 80
1793895098 78
1793895103 78
```
</details>

---

