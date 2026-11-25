---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 16:22:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 8 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (3 unique values: 28-34 cores)</summary>

```
1795641295 28
1795641300 28
1795641305 28
1795641310 28
1795641315 28
1795641320 28
1795641325 28
1795641331 28
1795641336 28
1795641341 28
1795641346 28
1795641351 28
1795641356 28
1795641361 28
1795641366 28
1795641371 28
1795641376 28
1795641381 28
1795641386 34
1795641391 34
```
</details>

---

