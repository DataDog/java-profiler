---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-20 12:09:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 724 |
| Sample Rate | 12.07/sec |
| Health Score | 754% |
| Threads | 10 |
| Allocations | 544 |

<details>
<summary>CPU Timeline (2 unique values: 21-23 cores)</summary>

```
1776701037 21
1776701042 21
1776701047 21
1776701052 21
1776701057 21
1776701062 21
1776701067 21
1776701072 21
1776701077 21
1776701082 21
1776701087 21
1776701092 21
1776701097 23
1776701102 23
1776701107 23
1776701112 23
1776701117 23
1776701122 23
1776701127 23
1776701132 23
```
</details>

---

