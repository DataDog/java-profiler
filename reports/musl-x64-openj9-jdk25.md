---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-30 11:47:35 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 460 |
| Sample Rate | 7.67/sec |
| Health Score | 479% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 11 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (2 unique values: 64-76 cores)</summary>

```
1793374865 76
1793374870 76
1793374875 76
1793374880 76
1793374885 76
1793374890 76
1793374895 76
1793374900 76
1793374905 76
1793374910 76
1793374915 76
1793374920 76
1793374925 76
1793374930 64
1793374935 64
1793374940 64
1793374945 64
1793374950 64
1793374955 64
1793374960 64
```
</details>

---

