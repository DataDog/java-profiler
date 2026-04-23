---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-23 13:43:25 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 54 |
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
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 689 |
| Sample Rate | 11.48/sec |
| Health Score | 718% |
| Threads | 11 |
| Allocations | 413 |

<details>
<summary>CPU Timeline (3 unique values: 54-61 cores)</summary>

```
1776965681 61
1776965686 61
1776965691 61
1776965696 61
1776965701 61
1776965706 61
1776965711 61
1776965716 61
1776965721 61
1776965726 61
1776965731 59
1776965736 59
1776965741 59
1776965746 59
1776965751 59
1776965756 59
1776965761 59
1776965766 59
1776965771 59
1776965776 59
```
</details>

---

