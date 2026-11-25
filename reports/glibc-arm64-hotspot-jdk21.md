---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 16:21:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 9 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795641351 47
1795641356 47
1795641361 47
1795641366 47
1795641371 47
1795641376 47
1795641381 47
1795641386 47
1795641391 47
1795641396 47
1795641401 47
1795641406 47
1795641411 47
1795641416 47
1795641421 64
1795641426 64
1795641431 64
1795641436 64
1795641441 64
1795641446 64
```
</details>

---

