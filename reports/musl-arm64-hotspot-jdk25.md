---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-23 10:30:05 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 7 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 570 |
| Sample Rate | 9.50/sec |
| Health Score | 594% |
| Threads | 10 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (5 unique values: 41-46 cores)</summary>

```
1792765507 41
1792765512 41
1792765517 41
1792765522 44
1792765527 44
1792765532 44
1792765537 44
1792765542 44
1792765547 44
1792765552 44
1792765557 44
1792765562 44
1792765567 44
1792765572 44
1792765577 44
1792765582 44
1792765587 44
1792765592 43
1792765598 43
1792765603 45
```
</details>

---

