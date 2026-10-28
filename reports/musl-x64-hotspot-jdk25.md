---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-27 20:59:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 7 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 384 |
| Sample Rate | 6.40/sec |
| Health Score | 400% |
| Threads | 8 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 9 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (3 unique values: 7-28 cores)</summary>

```
1793148864 7
1793148869 7
1793148874 7
1793148879 7
1793148884 28
1793148889 28
1793148894 28
1793148899 28
1793148904 10
1793148909 10
1793148914 10
1793148919 10
1793148924 10
1793148929 10
1793148934 10
1793148939 10
1793148944 10
1793148949 10
1793148954 10
1793148959 10
```
</details>

---

