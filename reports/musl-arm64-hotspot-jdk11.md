---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-23 10:30:05 EDT

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 231 |
| Sample Rate | 3.85/sec |
| Health Score | 241% |
| Threads | 14 |
| Allocations | 134 |

<details>
<summary>CPU Timeline (3 unique values: 37-40 cores)</summary>

```
1792765527 37
1792765532 37
1792765537 37
1792765542 37
1792765547 40
1792765552 40
1792765557 40
1792765562 40
1792765567 38
1792765572 38
1792765577 38
1792765582 38
1792765587 38
1792765592 38
1792765597 38
1792765602 38
1792765607 38
1792765612 38
1792765617 38
1792765622 38
```
</details>

---

