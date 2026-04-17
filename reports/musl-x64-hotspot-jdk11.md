---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-17 10:21:32 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 720 |
| Sample Rate | 12.00/sec |
| Health Score | 750% |
| Threads | 9 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 795 |
| Sample Rate | 13.25/sec |
| Health Score | 828% |
| Threads | 10 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (3 unique values: 56-60 cores)</summary>

```
1776435105 60
1776435110 60
1776435115 60
1776435120 60
1776435125 60
1776435130 60
1776435135 60
1776435140 60
1776435145 60
1776435150 59
1776435155 59
1776435160 59
1776435165 59
1776435170 59
1776435175 59
1776435180 56
1776435185 56
1776435190 56
1776435195 56
1776435200 56
```
</details>

---

