---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-29 07:57:21 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 414 |
| Sample Rate | 6.90/sec |
| Health Score | 431% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 11 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (4 unique values: 24-42 cores)</summary>

```
1793274801 24
1793274806 24
1793274811 24
1793274816 24
1793274821 24
1793274826 24
1793274831 24
1793274836 24
1793274841 29
1793274846 29
1793274851 29
1793274856 29
1793274861 29
1793274866 29
1793274871 29
1793274876 29
1793274881 29
1793274886 40
1793274891 40
1793274896 40
```
</details>

---

