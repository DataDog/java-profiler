---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 03:34:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 791 |
| Sample Rate | 13.18/sec |
| Health Score | 824% |
| Threads | 9 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 11 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (5 unique values: 32-44 cores)</summary>

```
1789716466 40
1789716471 42
1789716476 42
1789716481 44
1789716486 44
1789716491 34
1789716496 34
1789716501 34
1789716506 34
1789716511 34
1789716516 34
1789716521 34
1789716526 34
1789716531 34
1789716536 34
1789716541 34
1789716546 34
1789716551 34
1789716556 32
1789716561 32
```
</details>

---

