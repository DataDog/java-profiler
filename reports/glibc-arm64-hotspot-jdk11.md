---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-28 09:04:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 155 |
| Sample Rate | 2.58/sec |
| Health Score | 161% |
| Threads | 13 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 174 |
| Sample Rate | 2.90/sec |
| Health Score | 181% |
| Threads | 11 |
| Allocations | 90 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790600351 43
1790600357 43
1790600362 43
1790600367 43
1790600372 43
1790600377 43
1790600382 48
1790600387 48
1790600392 48
1790600397 48
1790600402 48
1790600407 43
1790600412 43
1790600417 43
1790600422 43
1790600427 43
1790600432 43
1790600437 43
1790600442 43
1790600447 43
```
</details>

---

