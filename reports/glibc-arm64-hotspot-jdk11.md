---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 03:34:33 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 657 |
| Sample Rate | 10.95/sec |
| Health Score | 684% |
| Threads | 9 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789716421 48
1789716426 48
1789716431 48
1789716436 48
1789716441 48
1789716446 48
1789716451 48
1789716456 48
1789716461 48
1789716466 48
1789716471 43
1789716476 43
1789716481 43
1789716486 43
1789716491 43
1789716496 43
1789716501 43
1789716506 43
1789716511 43
1789716516 43
```
</details>

---

