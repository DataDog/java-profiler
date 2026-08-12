---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-12 00:57:47 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 12 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 11 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1786510425 43
1786510430 43
1786510435 43
1786510440 43
1786510445 43
1786510450 43
1786510455 43
1786510460 43
1786510465 43
1786510470 43
1786510475 43
1786510480 43
1786510485 43
1786510490 48
1786510495 48
1786510500 48
1786510505 48
1786510510 48
1786510515 48
1786510520 48
```
</details>

---

