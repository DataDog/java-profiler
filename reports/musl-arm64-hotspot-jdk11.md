---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-28 07:58:53 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 9 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 27 |
| Sample Rate | 0.45/sec |
| Health Score | 28% |
| Threads | 8 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (2 unique values: 40-45 cores)</summary>

```
1790596431 40
1790596436 40
1790596441 40
1790596446 40
1790596451 40
1790596456 40
1790596461 40
1790596466 40
1790596471 40
1790596476 40
1790596481 40
1790596486 40
1790596491 40
1790596496 40
1790596501 40
1790596506 40
1790596511 40
1790596516 40
1790596521 40
1790596526 40
```
</details>

---

