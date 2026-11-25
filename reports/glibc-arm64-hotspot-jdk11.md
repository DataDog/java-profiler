---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 16:18:46 EST

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 6 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 28-33 cores)</summary>

```
1795641336 28
1795641341 28
1795641346 28
1795641351 28
1795641356 28
1795641361 28
1795641366 28
1795641371 33
1795641376 33
1795641381 33
1795641386 33
1795641391 33
1795641396 33
1795641401 33
1795641406 33
1795641411 33
1795641416 33
1795641421 33
1795641426 33
1795641432 33
```
</details>

---

