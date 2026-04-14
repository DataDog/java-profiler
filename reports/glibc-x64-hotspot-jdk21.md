---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-14 04:48:35 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 9 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (4 unique values: 23-29 cores)</summary>

```
1776156169 27
1776156174 27
1776156179 29
1776156184 29
1776156189 27
1776156194 27
1776156199 27
1776156204 27
1776156209 27
1776156214 27
1776156219 24
1776156224 24
1776156229 24
1776156234 24
1776156239 24
1776156244 24
1776156249 24
1776156254 24
1776156259 24
1776156264 24
```
</details>

---

