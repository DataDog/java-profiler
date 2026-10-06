---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-06 00:58:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 7 |
| Allocations | 40 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 279 |
| Sample Rate | 4.65/sec |
| Health Score | 291% |
| Threads | 11 |
| Allocations | 136 |

<details>
<summary>CPU Timeline (4 unique values: 28-48 cores)</summary>

```
1791262466 28
1791262471 28
1791262476 28
1791262481 28
1791262486 28
1791262491 28
1791262496 28
1791262501 28
1791262506 28
1791262511 28
1791262516 28
1791262521 28
1791262526 48
1791262531 48
1791262536 48
1791262541 48
1791262546 48
1791262551 48
1791262556 38
1791262561 38
```
</details>

---

