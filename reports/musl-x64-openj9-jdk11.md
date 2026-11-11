---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 00:08:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 688 |
| Sample Rate | 11.47/sec |
| Health Score | 717% |
| Threads | 10 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 964 |
| Sample Rate | 16.07/sec |
| Health Score | 1004% |
| Threads | 11 |
| Allocations | 548 |

<details>
<summary>CPU Timeline (3 unique values: 86-90 cores)</summary>

```
1794373435 88
1794373440 88
1794373445 90
1794373450 90
1794373455 88
1794373460 88
1794373465 88
1794373470 88
1794373475 90
1794373480 90
1794373485 90
1794373490 90
1794373495 90
1794373500 90
1794373505 90
1794373510 88
1794373515 88
1794373520 88
1794373525 88
1794373530 86
```
</details>

---

