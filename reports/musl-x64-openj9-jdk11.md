---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-14 01:04:05 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 9 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (4 unique values: 23-48 cores)</summary>

```
1791953932 45
1791953937 45
1791953942 45
1791953947 48
1791953952 48
1791953957 48
1791953962 48
1791953967 48
1791953972 48
1791953977 48
1791953982 48
1791953987 48
1791953992 48
1791953997 48
1791954002 48
1791954007 48
1791954012 48
1791954017 48
1791954022 48
1791954027 48
```
</details>

---

