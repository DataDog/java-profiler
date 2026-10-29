---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-29 13:19:45 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 788 |
| Sample Rate | 13.13/sec |
| Health Score | 821% |
| Threads | 10 |
| Allocations | 543 |

<details>
<summary>CPU Timeline (2 unique values: 79-84 cores)</summary>

```
1793293989 79
1793293994 79
1793293999 79
1793294004 79
1793294009 79
1793294014 79
1793294019 79
1793294024 79
1793294029 79
1793294034 84
1793294039 84
1793294044 84
1793294049 84
1793294054 84
1793294059 84
1793294064 84
1793294069 84
1793294074 84
1793294079 84
1793294084 84
```
</details>

---

