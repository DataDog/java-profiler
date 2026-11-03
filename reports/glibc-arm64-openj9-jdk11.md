---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-03 10:59:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 8 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793721307 43
1793721312 48
1793721317 48
1793721322 48
1793721327 48
1793721332 48
1793721337 48
1793721342 48
1793721347 48
1793721352 48
1793721357 48
1793721362 48
1793721367 48
1793721372 48
1793721377 48
1793721382 48
1793721387 48
1793721393 48
1793721398 48
1793721403 48
```
</details>

---

