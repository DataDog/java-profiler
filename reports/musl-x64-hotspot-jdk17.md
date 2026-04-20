---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-20 11:41:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 763 |
| Sample Rate | 12.72/sec |
| Health Score | 795% |
| Threads | 11 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1776699191 62
1776699196 64
1776699201 64
1776699206 64
1776699211 64
1776699216 64
1776699221 64
1776699226 64
1776699231 64
1776699236 64
1776699241 64
1776699246 62
1776699251 62
1776699256 62
1776699261 64
1776699266 64
1776699271 64
1776699276 64
1776699281 64
1776699286 64
```
</details>

---

