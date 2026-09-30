---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-30 15:17:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 8 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 14 |
| Allocations | 208 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1790795611 48
1790795616 48
1790795621 48
1790795626 48
1790795631 48
1790795636 48
1790795641 48
1790795646 28
1790795651 28
1790795656 28
1790795661 28
1790795666 28
1790795671 28
1790795676 28
1790795681 28
1790795686 28
1790795691 28
1790795696 28
1790795701 28
1790795706 28
```
</details>

---

