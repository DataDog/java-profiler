---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-06 06:41:35 EDT

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 8 |
| Allocations | 332 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 841 |
| Sample Rate | 14.02/sec |
| Health Score | 876% |
| Threads | 10 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (2 unique values: 86-88 cores)</summary>

```
1791282932 86
1791282937 86
1791282942 86
1791282947 88
1791282952 88
1791282957 86
1791282962 86
1791282967 86
1791282972 86
1791282977 86
1791282982 86
1791282987 86
1791282992 86
1791282997 88
1791283002 88
1791283007 88
1791283012 88
1791283017 88
1791283022 88
1791283027 88
```
</details>

---

