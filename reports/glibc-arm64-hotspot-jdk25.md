---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 16:21:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 12 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795641331 64
1795641336 64
1795641341 64
1795641346 64
1795641351 64
1795641356 64
1795641361 64
1795641366 64
1795641371 64
1795641376 64
1795641381 64
1795641386 64
1795641391 64
1795641396 64
1795641401 64
1795641406 64
1795641411 64
1795641416 64
1795641421 64
1795641426 64
```
</details>

---

