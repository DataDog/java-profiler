---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-23 03:58:19 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 739 |
| Sample Rate | 12.32/sec |
| Health Score | 770% |
| Threads | 11 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (3 unique values: 56-62 cores)</summary>

```
1776930821 60
1776930826 60
1776930831 60
1776930836 60
1776930841 60
1776930846 60
1776930851 60
1776930856 60
1776930861 62
1776930866 62
1776930871 62
1776930876 62
1776930881 62
1776930886 62
1776930891 60
1776930896 60
1776930901 60
1776930906 60
1776930911 60
1776930916 60
```
</details>

---

