---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-06 10:08:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 12 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 392 |
| Sample Rate | 6.53/sec |
| Health Score | 408% |
| Threads | 14 |
| Allocations | 136 |

<details>
<summary>CPU Timeline (2 unique values: 24-44 cores)</summary>

```
1791295392 44
1791295397 44
1791295402 44
1791295407 44
1791295412 44
1791295417 44
1791295422 44
1791295427 44
1791295432 24
1791295437 24
1791295443 24
1791295448 24
1791295453 24
1791295458 24
1791295463 24
1791295468 24
1791295473 24
1791295478 24
1791295483 24
1791295488 24
```
</details>

---

