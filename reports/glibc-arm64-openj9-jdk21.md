---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-04 13:32:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 243 |
| Sample Rate | 4.05/sec |
| Health Score | 253% |
| Threads | 11 |
| Allocations | 177 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 8 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (2 unique values: 53-64 cores)</summary>

```
1793816928 53
1793816933 53
1793816938 53
1793816943 53
1793816948 53
1793816953 53
1793816958 53
1793816963 64
1793816968 64
1793816973 64
1793816978 64
1793816983 53
1793816988 53
1793816993 53
1793816998 53
1793817003 53
1793817008 53
1793817013 53
1793817018 53
1793817023 53
```
</details>

---

