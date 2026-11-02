---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-02 10:41:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 415 |
| Sample Rate | 6.92/sec |
| Health Score | 432% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 11 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (4 unique values: 33-49 cores)</summary>

```
1793633756 35
1793633761 35
1793633766 35
1793633771 33
1793633776 33
1793633781 33
1793633786 33
1793633791 33
1793633796 33
1793633801 33
1793633806 33
1793633811 33
1793633816 33
1793633821 33
1793633826 33
1793633831 33
1793633836 33
1793633841 33
1793633846 33
1793633851 49
```
</details>

---

