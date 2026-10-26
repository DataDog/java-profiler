---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-26 14:59:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 268 |
| Sample Rate | 4.47/sec |
| Health Score | 279% |
| Threads | 8 |
| Allocations | 129 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 159 |
| Sample Rate | 2.65/sec |
| Health Score | 166% |
| Threads | 13 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (2 unique values: 26-31 cores)</summary>

```
1793040914 31
1793040919 31
1793040924 31
1793040929 31
1793040934 31
1793040939 31
1793040944 31
1793040949 31
1793040954 31
1793040959 31
1793040964 31
1793040969 31
1793040974 31
1793040979 31
1793040984 31
1793040989 31
1793040994 31
1793040999 31
1793041004 31
1793041009 31
```
</details>

---

