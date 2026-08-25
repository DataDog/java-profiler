---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-25 11:03:31 EDT

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
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 45 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 11 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1787669922 48
1787669927 48
1787669932 48
1787669937 48
1787669942 48
1787669947 48
1787669952 48
1787669957 48
1787669962 48
1787669967 48
1787669972 48
1787669977 48
1787669982 48
1787669987 48
1787669992 48
1787669997 48
1787670002 48
1787670007 48
1787670012 48
1787670017 48
```
</details>

---

