---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-11 13:17:32 EDT

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 11 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 907 |
| Sample Rate | 15.12/sec |
| Health Score | 945% |
| Threads | 13 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (5 unique values: 66-75 cores)</summary>

```
1773249100 67
1773249105 67
1773249110 72
1773249115 72
1773249120 72
1773249125 66
1773249130 66
1773249135 73
1773249140 73
1773249145 73
1773249150 73
1773249155 73
1773249160 75
1773249165 75
1773249170 75
1773249175 75
1773249180 75
1773249185 75
1773249190 75
1773249195 75
```
</details>

---

