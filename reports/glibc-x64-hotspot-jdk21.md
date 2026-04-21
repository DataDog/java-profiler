---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-21 14:31:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 9 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 915 |
| Sample Rate | 15.25/sec |
| Health Score | 953% |
| Threads | 11 |
| Allocations | 426 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1776795826 64
1776795831 64
1776795836 64
1776795841 60
1776795846 60
1776795851 60
1776795856 60
1776795861 60
1776795866 60
1776795871 60
1776795876 60
1776795881 60
1776795886 60
1776795891 60
1776795896 60
1776795901 60
1776795906 60
1776795911 60
1776795916 60
1776795921 60
```
</details>

---

