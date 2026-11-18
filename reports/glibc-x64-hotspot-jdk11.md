---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 05:35:54 EST

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 8 |
| Allocations | 332 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 770 |
| Sample Rate | 12.83/sec |
| Health Score | 802% |
| Threads | 10 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (4 unique values: 55-73 cores)</summary>

```
1794997808 55
1794997813 55
1794997818 55
1794997823 55
1794997828 55
1794997833 55
1794997838 55
1794997843 71
1794997848 71
1794997853 71
1794997858 71
1794997863 71
1794997868 71
1794997873 71
1794997878 71
1794997883 71
1794997888 71
1794997893 73
1794997898 73
1794997903 73
```
</details>

---

