---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-24 17:03:59 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 380 |
| Sample Rate | 6.33/sec |
| Health Score | 396% |
| Threads | 8 |
| Allocations | 425 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 216 |
| Sample Rate | 3.60/sec |
| Health Score | 225% |
| Threads | 12 |
| Allocations | 148 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1777064252 30
1777064257 30
1777064262 32
1777064267 32
1777064272 32
1777064277 32
1777064282 32
1777064287 32
1777064292 32
1777064297 32
1777064302 32
1777064307 32
1777064312 32
1777064317 32
1777064322 32
1777064327 32
1777064332 32
1777064337 32
1777064342 32
1777064347 32
```
</details>

---

