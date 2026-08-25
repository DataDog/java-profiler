---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-25 16:41:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 9 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 10 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1787690252 96
1787690257 96
1787690262 96
1787690267 96
1787690272 94
1787690277 94
1787690282 94
1787690287 94
1787690292 94
1787690297 94
1787690302 94
1787690307 94
1787690312 94
1787690317 94
1787690322 94
1787690327 94
1787690332 94
1787690337 94
1787690342 94
1787690347 94
```
</details>

---

