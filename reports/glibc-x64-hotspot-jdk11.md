---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 05:46:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 817 |
| Sample Rate | 13.62/sec |
| Health Score | 851% |
| Threads | 9 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (3 unique values: 51-56 cores)</summary>

```
1795084990 53
1795084995 53
1795085000 53
1795085005 53
1795085010 53
1795085015 51
1795085020 51
1795085025 51
1795085030 51
1795085035 51
1795085040 51
1795085045 51
1795085050 51
1795085055 51
1795085060 53
1795085065 53
1795085070 53
1795085075 53
1795085080 53
1795085085 53
```
</details>

---

