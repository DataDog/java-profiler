---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-11 09:28:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 77 |

<details>
<summary>CPU Timeline (2 unique values: 30-64 cores)</summary>

```
1786454555 64
1786454560 64
1786454565 64
1786454570 64
1786454575 64
1786454580 64
1786454585 64
1786454590 64
1786454595 64
1786454600 64
1786454605 64
1786454610 64
1786454615 64
1786454620 30
1786454625 30
1786454630 30
1786454635 30
1786454640 30
1786454645 30
1786454650 30
```
</details>

---

