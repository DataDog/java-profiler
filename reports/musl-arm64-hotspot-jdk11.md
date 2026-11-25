---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 16:22:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 29 |
| Sample Rate | 0.48/sec |
| Health Score | 30% |
| Threads | 8 |
| Allocations | 17 |

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
1795641412 47
1795641417 47
1795641422 64
```
</details>

---

