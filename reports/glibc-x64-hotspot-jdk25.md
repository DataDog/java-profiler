---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-11 15:21:53 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 380 |
| Sample Rate | 6.33/sec |
| Health Score | 396% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 9 |
| Allocations | 544 |

<details>
<summary>CPU Timeline (3 unique values: 34-43 cores)</summary>

```
1791746258 42
1791746263 42
1791746268 42
1791746273 42
1791746278 42
1791746283 42
1791746288 42
1791746293 42
1791746298 34
1791746303 34
1791746308 34
1791746313 34
1791746318 34
1791746323 34
1791746328 34
1791746333 34
1791746338 34
1791746343 34
1791746348 34
1791746353 34
```
</details>

---

