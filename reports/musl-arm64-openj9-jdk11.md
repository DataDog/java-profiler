---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-16 10:55:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 13 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776350976 64
1776350981 64
1776350986 64
1776350991 64
1776350996 64
1776351001 64
1776351006 64
1776351011 64
1776351016 64
1776351021 64
1776351026 64
1776351031 64
1776351036 64
1776351041 64
1776351046 64
1776351051 64
1776351056 64
1776351061 64
1776351066 64
1776351071 64
```
</details>

---

