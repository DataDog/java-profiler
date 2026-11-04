---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 05:47:32 EST

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
| CPU Cores (start) | 93 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 8 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 8 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (3 unique values: 59-93 cores)</summary>

```
1793788929 93
1793788934 93
1793788939 93
1793788944 81
1793788949 81
1793788954 81
1793788959 81
1793788964 81
1793788969 81
1793788974 81
1793788979 81
1793788984 81
1793788989 81
1793788994 81
1793788999 81
1793789004 59
1793789009 59
1793789014 59
1793789019 59
1793789024 59
```
</details>

---

