---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-30 10:04:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 13 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1777557242 44
1777557247 44
1777557252 44
1777557257 44
1777557262 44
1777557267 44
1777557272 44
1777557277 44
1777557282 48
1777557287 48
1777557292 48
1777557297 48
1777557302 43
1777557307 43
1777557312 43
1777557317 43
1777557322 48
1777557327 48
1777557332 48
1777557337 48
```
</details>

---

