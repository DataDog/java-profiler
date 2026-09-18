---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 03:34:33 EDT

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 145 |
| Sample Rate | 2.42/sec |
| Health Score | 151% |
| Threads | 9 |
| Allocations | 87 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (3 unique values: 20-42 cores)</summary>

```
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
1789716566 24
```
</details>

---

