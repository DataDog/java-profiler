---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 06:01:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 11 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (5 unique values: 53-68 cores)</summary>

```
1795431347 68
1795431352 62
1795431357 62
1795431362 62
1795431367 62
1795431372 62
1795431377 62
1795431382 62
1795431387 62
1795431392 64
1795431397 64
1795431402 64
1795431407 55
1795431412 55
1795431417 55
1795431422 55
1795431427 55
1795431432 55
1795431437 55
1795431442 55
```
</details>

---

