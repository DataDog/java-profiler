---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 05:00:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 245 |
| Sample Rate | 4.08/sec |
| Health Score | 255% |
| Threads | 11 |
| Allocations | 141 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 12 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (3 unique values: 36-48 cores)</summary>

```
1794477322 36
1794477327 48
1794477332 48
1794477337 48
1794477342 48
1794477347 48
1794477352 48
1794477357 48
1794477362 43
1794477367 43
1794477372 43
1794477377 43
1794477382 43
1794477387 43
1794477392 43
1794477397 43
1794477402 43
1794477407 43
1794477412 43
1794477417 43
```
</details>

---

