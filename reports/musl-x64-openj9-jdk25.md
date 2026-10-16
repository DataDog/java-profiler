---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-16 04:44:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 8 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 387 |
| Sample Rate | 6.45/sec |
| Health Score | 403% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 9 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (1 unique values: 8-8 cores)</summary>

```
1792139931 8
1792139936 8
1792139941 8
1792139946 8
1792139951 8
1792139956 8
1792139961 8
1792139966 8
1792139971 8
1792139976 8
1792139981 8
1792139986 8
1792139991 8
1792139996 8
1792140001 8
1792140006 8
1792140011 8
1792140016 8
1792140021 8
1792140026 8
```
</details>

---

