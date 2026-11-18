---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 10:28:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 316 |
| Sample Rate | 5.27/sec |
| Health Score | 329% |
| Threads | 11 |
| Allocations | 120 |

<details>
<summary>CPU Timeline (2 unique values: 33-38 cores)</summary>

```
1795015394 33
1795015399 33
1795015404 33
1795015409 33
1795015414 33
1795015419 33
1795015424 33
1795015429 38
1795015434 38
1795015439 38
1795015444 38
1795015449 38
1795015454 38
1795015459 38
1795015464 38
1795015469 38
1795015474 38
1795015479 38
1795015484 38
1795015489 38
```
</details>

---

