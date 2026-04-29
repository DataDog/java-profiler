---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-29 14:43:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 11 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (4 unique values: 90-96 cores)</summary>

```
1777487913 94
1777487918 94
1777487923 94
1777487928 94
1777487933 94
1777487938 94
1777487943 94
1777487948 94
1777487953 96
1777487958 96
1777487963 96
1777487968 96
1777487973 96
1777487978 96
1777487983 96
1777487988 96
1777487993 96
1777487998 96
1777488003 96
1777488008 96
```
</details>

---

