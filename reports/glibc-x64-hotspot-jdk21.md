---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-24 17:03:59 EDT

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 145 |
| Sample Rate | 2.42/sec |
| Health Score | 151% |
| Threads | 8 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 135 |
| Sample Rate | 2.25/sec |
| Health Score | 141% |
| Threads | 12 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (3 unique values: 19-26 cores)</summary>

```
1777064257 26
1777064262 26
1777064267 26
1777064272 26
1777064277 26
1777064282 26
1777064287 24
1777064292 24
1777064297 24
1777064302 24
1777064307 24
1777064312 24
1777064317 24
1777064322 24
1777064327 24
1777064332 24
1777064337 19
1777064342 19
1777064347 19
1777064352 19
```
</details>

---

