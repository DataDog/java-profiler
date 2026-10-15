---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-15 11:06:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 290 |
| Sample Rate | 4.83/sec |
| Health Score | 302% |
| Threads | 10 |
| Allocations | 185 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 7 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (3 unique values: 37-48 cores)</summary>

```
1792076372 37
1792076377 37
1792076382 37
1792076387 37
1792076392 37
1792076397 48
1792076402 48
1792076408 48
1792076413 48
1792076418 48
1792076423 48
1792076428 38
1792076433 38
1792076438 38
1792076443 38
1792076448 38
1792076453 38
1792076458 38
1792076463 38
1792076468 38
```
</details>

---

