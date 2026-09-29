---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-29 07:48:59 EDT

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 872 |
| Sample Rate | 14.53/sec |
| Health Score | 908% |
| Threads | 12 |
| Allocations | 426 |

<details>
<summary>CPU Timeline (3 unique values: 85-87 cores)</summary>

```
1790682246 86
1790682251 86
1790682256 86
1790682261 86
1790682266 86
1790682271 85
1790682276 85
1790682281 85
1790682286 85
1790682291 85
1790682296 85
1790682301 85
1790682306 85
1790682311 85
1790682316 85
1790682321 85
1790682326 85
1790682331 85
1790682336 87
1790682341 87
```
</details>

---

