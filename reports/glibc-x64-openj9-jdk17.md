---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-06 06:13:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 8 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 842 |
| Sample Rate | 14.03/sec |
| Health Score | 877% |
| Threads | 9 |
| Allocations | 428 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1772795219 30
1772795224 30
1772795229 30
1772795234 30
1772795239 30
1772795244 30
1772795249 30
1772795254 30
1772795259 30
1772795264 30
1772795269 30
1772795274 30
1772795279 30
1772795284 30
1772795289 30
1772795294 30
1772795299 30
1772795304 32
1772795309 32
1772795314 32
```
</details>

---

