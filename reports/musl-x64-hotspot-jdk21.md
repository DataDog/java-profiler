---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-22 12:31:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 11 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (5 unique values: 46-71 cores)</summary>

```
1790093887 47
1790093892 47
1790093897 47
1790093902 47
1790093907 47
1790093912 47
1790093917 47
1790093922 71
1790093927 71
1790093932 48
1790093937 48
1790093942 48
1790093947 48
1790093952 48
1790093957 48
1790093962 46
1790093967 46
1790093972 54
1790093977 54
1790093982 54
```
</details>

---

