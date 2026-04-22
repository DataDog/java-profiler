---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-22 13:04:06 EDT

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 9 |
| Allocations | 559 |

<details>
<summary>CPU Timeline (2 unique values: 24-55 cores)</summary>

```
1776876843 55
1776876848 55
1776876853 55
1776876858 55
1776876863 55
1776876868 24
1776876873 24
1776876878 24
1776876883 24
1776876888 24
1776876893 24
1776876898 24
1776876903 24
1776876908 24
1776876913 24
1776876918 24
1776876923 24
1776876929 24
1776876934 24
1776876939 24
```
</details>

---

