---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 12:58:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 779 |
| Sample Rate | 12.98/sec |
| Health Score | 811% |
| Threads | 11 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (2 unique values: 59-62 cores)</summary>

```
1794592485 62
1794592490 62
1794592495 62
1794592500 62
1794592505 62
1794592510 62
1794592515 62
1794592520 62
1794592525 62
1794592530 62
1794592535 62
1794592540 62
1794592545 62
1794592550 62
1794592556 62
1794592561 62
1794592566 59
1794592571 59
1794592576 59
1794592581 59
```
</details>

---

