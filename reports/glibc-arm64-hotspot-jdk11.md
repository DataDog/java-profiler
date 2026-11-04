---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 13:32:31 EST

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
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 6 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793816874 48
1793816879 48
1793816884 48
1793816889 48
1793816894 48
1793816899 48
1793816904 48
1793816909 48
1793816914 48
1793816919 48
1793816924 48
1793816929 48
1793816934 48
1793816939 48
1793816944 48
1793816949 48
1793816954 48
1793816959 48
1793816964 48
1793816969 48
```
</details>

---

