---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 16:22:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
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
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 6 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795641326 47
1795641331 47
1795641336 47
1795641341 47
1795641346 47
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
```
</details>

---

