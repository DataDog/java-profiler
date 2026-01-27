---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-01-27 14:14:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 436 |
| Sample Rate | 14.53/sec |
| Health Score | 908% |
| Threads | 8 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 21.47/sec |
| Health Score | 1342% |
| Threads | 10 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1769540947 32
1769540952 32
1769540957 32
1769540962 30
1769540967 30
1769540972 30
1769540977 32
1769540982 32
1769540987 32
1769540992 32
1769540997 32
1769541002 32
1769541007 32
1769541012 32
1769541017 32
1769541022 32
1769541027 32
1769541032 32
1769541037 32
1769541042 32
```
</details>

---

