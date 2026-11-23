---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 05:58:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 400 |
| Sample Rate | 6.67/sec |
| Health Score | 417% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 10 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (5 unique values: 21-30 cores)</summary>

```
1795431244 21
1795431249 21
1795431254 21
1795431259 23
1795431264 23
1795431269 23
1795431274 23
1795431279 29
1795431284 29
1795431289 27
1795431294 27
1795431299 27
1795431304 27
1795431309 27
1795431314 27
1795431319 27
1795431324 27
1795431329 30
1795431334 30
1795431339 30
```
</details>

---

