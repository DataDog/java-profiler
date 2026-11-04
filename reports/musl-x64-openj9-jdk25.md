---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-04 13:32:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 11 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (7 unique values: 45-64 cores)</summary>

```
1793816855 53
1793816860 53
1793816865 53
1793816870 53
1793816875 53
1793816880 53
1793816885 53
1793816890 53
1793816895 53
1793816900 51
1793816905 51
1793816910 51
1793816915 45
1793816920 45
1793816925 47
1793816930 47
1793816935 47
1793816940 47
1793816945 47
1793816950 63
```
</details>

---

