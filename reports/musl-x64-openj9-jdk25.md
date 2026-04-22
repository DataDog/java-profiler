---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-22 14:05:08 EDT

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 9 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 11 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (5 unique values: 60-65 cores)</summary>

```
1776880782 63
1776880787 63
1776880792 63
1776880797 65
1776880802 65
1776880807 65
1776880812 65
1776880817 65
1776880822 65
1776880827 65
1776880832 65
1776880837 65
1776880842 65
1776880847 65
1776880852 65
1776880857 65
1776880862 65
1776880868 65
1776880873 62
1776880878 62
```
</details>

---

