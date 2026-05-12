---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-12 02:56:27 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 10 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 13 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778568626 64
1778568631 64
1778568636 64
1778568641 64
1778568646 64
1778568651 64
1778568656 64
1778568661 64
1778568666 64
1778568671 64
1778568676 64
1778568681 64
1778568686 64
1778568691 64
1778568696 64
1778568701 64
1778568706 64
1778568711 64
1778568716 64
1778568721 64
```
</details>

---

