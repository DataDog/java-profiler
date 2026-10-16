---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-16 04:44:30 EDT

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 10 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (2 unique values: 74-96 cores)</summary>

```
1792139934 74
1792139939 74
1792139944 74
1792139949 74
1792139954 74
1792139959 74
1792139964 74
1792139969 74
1792139974 74
1792139979 96
1792139984 96
1792139989 96
1792139994 96
1792139999 96
1792140004 96
1792140009 96
1792140014 96
1792140019 96
1792140024 96
1792140029 96
```
</details>

---

