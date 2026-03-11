---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-11 14:07:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 10 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 13 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (3 unique values: 56-68 cores)</summary>

```
1773252135 56
1773252140 56
1773252145 68
1773252150 68
1773252155 68
1773252160 68
1773252165 68
1773252170 65
1773252175 65
1773252180 65
1773252185 65
1773252190 65
1773252195 65
1773252200 65
1773252205 65
1773252210 65
1773252215 65
1773252220 65
1773252225 65
1773252230 65
```
</details>

---

