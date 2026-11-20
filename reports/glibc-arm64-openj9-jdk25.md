---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-20 08:32:50 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 689 |
| Sample Rate | 11.48/sec |
| Health Score | 718% |
| Threads | 10 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795181328 50
1795181333 50
1795181338 50
1795181343 50
1795181348 50
1795181353 50
1795181358 50
1795181363 50
1795181368 50
1795181373 50
1795181379 50
1795181384 50
1795181389 50
1795181394 50
1795181399 50
1795181404 50
1795181409 50
1795181414 50
1795181419 50
1795181424 50
```
</details>

---

