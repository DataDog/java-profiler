---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-01-29 08:17:25 EST

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 18.53/sec |
| Health Score | 1158% |
| Threads | 10 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 924 |
| Sample Rate | 30.80/sec |
| Health Score | 1925% |
| Threads | 12 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (2 unique values: 83-85 cores)</summary>

```
1769692291 83
1769692296 83
1769692301 83
1769692307 85
1769692312 85
1769692317 85
1769692322 85
1769692327 85
1769692332 85
1769692337 85
1769692342 85
1769692347 85
1769692352 85
1769692357 85
1769692362 85
1769692367 85
1769692372 85
1769692377 85
1769692382 85
1769692387 85
```
</details>

---

