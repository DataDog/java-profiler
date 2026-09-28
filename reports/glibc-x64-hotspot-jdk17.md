---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-28 10:16:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 10 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 699 |
| Sample Rate | 11.65/sec |
| Health Score | 728% |
| Threads | 11 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (2 unique values: 60-61 cores)</summary>

```
1790604707 60
1790604712 60
1790604717 60
1790604722 60
1790604727 60
1790604732 60
1790604737 60
1790604742 60
1790604747 61
1790604752 61
1790604757 61
1790604762 61
1790604767 61
1790604772 61
1790604777 61
1790604782 61
1790604787 61
1790604792 61
1790604797 61
1790604802 61
```
</details>

---

