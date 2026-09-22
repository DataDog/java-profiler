---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-22 12:34:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 404 |
| Sample Rate | 6.73/sec |
| Health Score | 421% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 11 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (4 unique values: 52-79 cores)</summary>

```
1790094219 52
1790094224 52
1790094229 52
1790094234 52
1790094239 62
1790094244 62
1790094249 62
1790094254 62
1790094259 62
1790094264 62
1790094269 62
1790094274 62
1790094279 62
1790094284 79
1790094289 79
1790094294 79
1790094299 79
1790094304 77
1790094309 77
1790094314 77
```
</details>

---

