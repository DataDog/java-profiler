---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-12 08:46:05 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 8 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 10 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (2 unique values: 25-30 cores)</summary>

```
1786538525 30
1786538530 30
1786538535 30
1786538540 30
1786538545 30
1786538550 30
1786538555 30
1786538560 30
1786538565 30
1786538570 25
1786538575 25
1786538580 25
1786538585 25
1786538590 25
1786538595 25
1786538600 25
1786538605 25
1786538610 25
1786538615 25
1786538620 25
```
</details>

---

