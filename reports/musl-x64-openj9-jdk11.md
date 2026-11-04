---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 13:32:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 771 |
| Sample Rate | 12.85/sec |
| Health Score | 803% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 777 |
| Sample Rate | 12.95/sec |
| Health Score | 809% |
| Threads | 10 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (4 unique values: 76-91 cores)</summary>

```
1793816870 89
1793816875 91
1793816880 91
1793816885 91
1793816890 84
1793816895 84
1793816900 84
1793816905 84
1793816910 84
1793816915 84
1793816920 84
1793816925 84
1793816930 84
1793816935 84
1793816940 84
1793816945 84
1793816950 84
1793816955 84
1793816960 84
1793816965 76
```
</details>

---

