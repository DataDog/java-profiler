---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-28 07:43:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 9 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 273 |
| Sample Rate | 4.55/sec |
| Health Score | 284% |
| Threads | 13 |
| Allocations | 125 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793187396 48
1793187401 48
1793187406 48
1793187411 48
1793187416 48
1793187421 48
1793187426 48
1793187431 43
1793187436 43
1793187441 43
1793187446 43
1793187451 43
1793187456 43
1793187461 43
1793187466 43
1793187471 43
1793187476 43
1793187481 43
1793187486 43
1793187491 43
```
</details>

---

