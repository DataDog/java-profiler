---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-16 12:01:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 10 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 852 |
| Sample Rate | 14.20/sec |
| Health Score | 887% |
| Threads | 11 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (6 unique values: 62-87 cores)</summary>

```
1776355082 67
1776355087 67
1776355092 67
1776355097 62
1776355102 62
1776355107 62
1776355112 87
1776355117 87
1776355122 70
1776355127 70
1776355132 70
1776355137 70
1776355142 70
1776355147 65
1776355152 65
1776355157 69
1776355162 69
1776355167 69
1776355172 69
1776355177 69
```
</details>

---

