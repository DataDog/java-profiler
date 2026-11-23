---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-22 20:31:40 EST

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 803 |
| Sample Rate | 13.38/sec |
| Health Score | 836% |
| Threads | 10 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (6 unique values: 23-57 cores)</summary>

```
1795397189 57
1795397194 55
1795397199 55
1795397204 38
1795397209 38
1795397214 38
1795397219 36
1795397224 36
1795397229 36
1795397235 36
1795397240 36
1795397245 36
1795397250 36
1795397255 36
1795397260 38
1795397265 38
1795397270 40
1795397275 40
1795397280 40
1795397285 40
```
</details>

---

