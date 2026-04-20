---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-04-20 10:34:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 180 |
| Sample Rate | 3.00/sec |
| Health Score | 188% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 340 |
| Sample Rate | 5.67/sec |
| Health Score | 354% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 20-28 cores)</summary>

```
1776695062 28
1776695067 28
1776695072 28
1776695077 28
1776695082 28
1776695087 28
1776695092 28
1776695097 28
1776695102 28
1776695107 28
1776695112 28
1776695117 28
1776695122 28
1776695127 28
1776695132 28
1776695137 28
1776695142 28
1776695147 28
1776695152 23
1776695157 23
```
</details>

---

