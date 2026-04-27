---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-27 05:15:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 830 |
| Sample Rate | 13.83/sec |
| Health Score | 864% |
| Threads | 9 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (3 unique values: 25-30 cores)</summary>

```
1777280989 25
1777280994 25
1777280999 25
1777281004 25
1777281009 25
1777281014 25
1777281020 25
1777281025 25
1777281030 25
1777281035 25
1777281040 27
1777281045 27
1777281050 27
1777281055 27
1777281060 27
1777281065 27
1777281070 27
1777281075 27
1777281080 27
1777281085 27
```
</details>

---

