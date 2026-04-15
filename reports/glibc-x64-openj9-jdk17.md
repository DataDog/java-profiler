---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-15 11:36:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 9 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 10 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (6 unique values: 33-64 cores)</summary>

```
1776266696 33
1776266701 33
1776266706 33
1776266711 33
1776266716 37
1776266721 37
1776266726 37
1776266731 37
1776266736 38
1776266741 38
1776266746 38
1776266751 38
1776266756 64
1776266761 64
1776266766 64
1776266771 46
1776266776 46
1776266781 46
1776266786 46
1776266791 46
```
</details>

---

