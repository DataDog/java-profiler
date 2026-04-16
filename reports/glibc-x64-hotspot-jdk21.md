---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-16 05:53:23 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 426 |
| Sample Rate | 7.10/sec |
| Health Score | 444% |
| Threads | 8 |
| Allocations | 331 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 750 |
| Sample Rate | 12.50/sec |
| Health Score | 781% |
| Threads | 10 |
| Allocations | 422 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1776332842 32
1776332847 32
1776332852 32
1776332857 30
1776332862 30
1776332867 32
1776332872 32
1776332877 32
1776332883 32
1776332888 32
1776332893 32
1776332898 32
1776332903 32
1776332908 32
1776332913 32
1776332918 32
1776332923 32
1776332928 32
1776332933 32
1776332938 28
```
</details>

---

