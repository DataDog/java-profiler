---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-16 04:26:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 284 |
| Sample Rate | 4.73/sec |
| Health Score | 296% |
| Threads | 10 |
| Allocations | 157 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 15 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (3 unique values: 40-56 cores)</summary>

```
1792138959 40
1792138964 40
1792138969 40
1792138974 45
1792138979 45
1792138984 45
1792138989 45
1792138994 45
1792138999 45
1792139004 45
1792139009 45
1792139014 45
1792139019 45
1792139024 45
1792139029 45
1792139034 56
1792139039 56
1792139044 56
1792139049 56
1792139054 56
```
</details>

---

