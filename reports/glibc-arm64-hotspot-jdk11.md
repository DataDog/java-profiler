---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 16:20:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 11 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 29 |
| Sample Rate | 0.48/sec |
| Health Score | 30% |
| Threads | 10 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (3 unique values: 30-47 cores)</summary>

```
1795641356 31
1795641361 31
1795641366 31
1795641371 31
1795641376 31
1795641381 31
1795641386 31
1795641391 31
1795641396 31
1795641402 31
1795641407 31
1795641412 31
1795641417 31
1795641422 31
1795641427 31
1795641432 31
1795641437 31
1795641442 31
1795641447 31
1795641452 31
```
</details>

---

