---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-02 10:41:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 13 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (2 unique values: 36-38 cores)</summary>

```
1793633756 38
1793633761 38
1793633766 38
1793633771 38
1793633776 38
1793633781 38
1793633786 38
1793633791 38
1793633796 38
1793633801 38
1793633806 38
1793633811 38
1793633816 38
1793633821 38
1793633826 38
1793633831 38
1793633836 38
1793633841 38
1793633846 38
1793633851 38
```
</details>

---

