---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-14 01:04:03 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 12 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (3 unique values: 46-51 cores)</summary>

```
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
1791954027 46
1791954032 46
1791954037 51
1791954042 51
1791954047 51
1791954052 51
```
</details>

---

