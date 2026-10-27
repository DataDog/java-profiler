---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-26 20:50:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 12 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (1 unique values: 41-41 cores)</summary>

```
1793061949 41
1793061954 41
1793061959 41
1793061964 41
1793061969 41
1793061974 41
1793061979 41
1793061984 41
1793061989 41
1793061994 41
1793061999 41
1793062004 41
1793062009 41
1793062014 41
1793062019 41
1793062024 41
1793062029 41
1793062034 41
1793062039 41
1793062044 41
```
</details>

---

