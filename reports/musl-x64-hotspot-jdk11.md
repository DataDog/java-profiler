---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-05 10:57:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 746 |
| Sample Rate | 12.43/sec |
| Health Score | 777% |
| Threads | 9 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (3 unique values: 82-86 cores)</summary>

```
1793893947 82
1793893952 82
1793893957 82
1793893962 82
1793893967 82
1793893972 82
1793893977 82
1793893982 82
1793893987 82
1793893992 86
1793893997 86
1793894002 86
1793894007 83
1793894012 83
1793894017 83
1793894022 83
1793894028 83
1793894033 83
1793894038 83
1793894043 83
```
</details>

---

