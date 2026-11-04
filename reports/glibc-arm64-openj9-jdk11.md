---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 13:32:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 734 |
| Sample Rate | 12.23/sec |
| Health Score | 764% |
| Threads | 8 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 31 |
| Sample Rate | 0.52/sec |
| Health Score | 32% |
| Threads | 9 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793816928 43
1793816933 43
1793816938 43
1793816943 43
1793816948 48
1793816953 48
1793816958 48
1793816963 48
1793816968 48
1793816973 48
1793816978 48
1793816983 48
1793816988 48
1793816993 48
1793816998 48
1793817003 48
1793817008 48
1793817013 48
1793817018 48
1793817023 48
```
</details>

---

