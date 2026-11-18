---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 13:48:35 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 9 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 37 |
| Sample Rate | 0.62/sec |
| Health Score | 39% |
| Threads | 10 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1795027375 32
1795027380 32
1795027385 32
1795027390 32
1795027395 32
1795027400 32
1795027405 32
1795027410 32
1795027415 32
1795027420 32
1795027425 32
1795027430 32
1795027435 32
1795027440 32
1795027445 32
1795027450 32
1795027455 32
1795027460 32
1795027465 32
1795027470 32
```
</details>

---

