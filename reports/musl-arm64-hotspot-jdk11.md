---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-13 11:08:22 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 31 |

<details>
<summary>CPU Timeline (3 unique values: 54-64 cores)</summary>

```
1778684519 64
1778684524 64
1778684529 64
1778684534 64
1778684540 64
1778684545 64
1778684550 64
1778684555 64
1778684560 64
1778684565 64
1778684570 64
1778684575 64
1778684580 64
1778684585 64
1778684590 64
1778684595 59
1778684600 59
1778684605 54
1778684610 54
1778684615 54
```
</details>

---

