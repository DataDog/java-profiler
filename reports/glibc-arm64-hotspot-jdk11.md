---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-15 11:06:38 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 9 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 387 |
| Sample Rate | 6.45/sec |
| Health Score | 403% |
| Threads | 13 |
| Allocations | 114 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792076352 48
1792076357 48
1792076362 48
1792076367 48
1792076372 48
1792076377 48
1792076382 48
1792076387 48
1792076392 48
1792076397 48
1792076402 48
1792076407 48
1792076412 48
1792076417 48
1792076422 48
1792076427 48
1792076432 48
1792076437 48
1792076442 43
1792076447 43
```
</details>

---

