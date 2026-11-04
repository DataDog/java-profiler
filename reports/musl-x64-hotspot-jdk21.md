---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-04 13:32:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 877 |
| Sample Rate | 14.62/sec |
| Health Score | 914% |
| Threads | 11 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (5 unique values: 70-89 cores)</summary>

```
1793816879 75
1793816884 75
1793816889 75
1793816894 75
1793816899 70
1793816904 70
1793816909 70
1793816914 70
1793816919 70
1793816924 70
1793816929 70
1793816934 85
1793816939 85
1793816944 85
1793816949 85
1793816954 85
1793816959 85
1793816964 87
1793816969 87
1793816974 87
```
</details>

---

