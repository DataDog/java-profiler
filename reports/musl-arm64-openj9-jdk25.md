---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-15 12:04:42 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 10 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1792079965 64
1792079970 64
1792079975 64
1792079980 64
1792079985 64
1792079990 64
1792079995 64
1792080000 64
1792080005 64
1792080010 64
1792080015 64
1792080020 64
1792080025 64
1792080030 64
1792080035 64
1792080040 64
1792080045 64
1792080050 64
1792080055 64
1792080060 64
```
</details>

---

