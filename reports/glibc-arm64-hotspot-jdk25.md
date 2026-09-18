---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 03:34:33 EDT

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 142 |
| Sample Rate | 2.37/sec |
| Health Score | 148% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 13 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (3 unique values: 20-42 cores)</summary>

```
1789716466 20
1789716471 20
1789716476 20
1789716481 20
1789716486 20
1789716491 20
1789716496 20
1789716501 20
1789716506 20
1789716511 20
1789716516 20
1789716521 20
1789716526 20
1789716531 20
1789716536 20
1789716541 20
1789716546 42
1789716551 42
1789716556 24
1789716561 24
```
</details>

---

