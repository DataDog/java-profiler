---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-04-23 03:58:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 165 |
| Sample Rate | 2.75/sec |
| Health Score | 172% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 427 |
| Sample Rate | 7.12/sec |
| Health Score | 445% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 28-36 cores)</summary>

```
1776930838 31
1776930843 31
1776930848 31
1776930853 31
1776930858 31
1776930863 31
1776930868 31
1776930873 36
1776930878 36
1776930883 36
1776930888 28
1776930893 28
1776930899 33
1776930904 33
1776930909 33
1776930914 33
1776930919 33
1776930924 33
1776930929 33
1776930934 33
```
</details>

---

