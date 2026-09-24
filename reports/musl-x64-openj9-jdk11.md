---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-24 14:06:10 EDT

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
| CPU Cores (start) | 17 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 10 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (3 unique values: 17-64 cores)</summary>

```
1790272857 17
1790272862 17
1790272867 17
1790272872 64
1790272877 64
1790272882 39
1790272887 39
1790272892 39
1790272897 39
1790272902 39
1790272907 39
1790272912 39
1790272917 39
1790272922 39
1790272927 39
1790272932 39
1790272937 39
1790272942 39
1790272947 39
1790272952 39
```
</details>

---

