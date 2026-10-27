---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-27 01:05:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 262 |
| Sample Rate | 4.37/sec |
| Health Score | 273% |
| Threads | 11 |
| Allocations | 138 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1793077244 48
1793077249 48
1793077254 48
1793077259 43
1793077264 43
1793077269 43
1793077274 43
1793077279 43
1793077284 43
1793077289 43
1793077294 43
1793077299 43
1793077304 43
1793077309 43
1793077314 43
1793077319 43
1793077324 43
1793077329 43
1793077334 43
1793077339 38
```
</details>

---

