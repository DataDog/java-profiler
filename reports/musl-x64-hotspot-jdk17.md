---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-01-30 04:28:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 15.57/sec |
| Health Score | 973% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 759 |
| Sample Rate | 25.30/sec |
| Health Score | 1581% |
| Threads | 11 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (3 unique values: 82-96 cores)</summary>

```
1769764879 96
1769764884 96
1769764889 96
1769764894 96
1769764899 96
1769764904 96
1769764909 96
1769764914 96
1769764919 96
1769764924 96
1769764929 96
1769764934 96
1769764939 96
1769764944 96
1769764949 96
1769764954 82
1769764959 82
1769764964 82
1769764969 82
1769764974 84
```
</details>

---

