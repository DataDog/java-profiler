---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-05 11:16:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 8 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 10 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (2 unique values: 70-87 cores)</summary>

```
1793895017 87
1793895022 87
1793895027 87
1793895032 87
1793895037 87
1793895042 87
1793895047 87
1793895052 87
1793895057 87
1793895062 87
1793895067 70
1793895072 70
1793895077 70
1793895082 70
1793895087 70
1793895092 70
1793895097 70
1793895102 70
1793895107 70
1793895112 70
```
</details>

---

