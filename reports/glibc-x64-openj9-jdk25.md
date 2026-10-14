---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-14 10:47:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 386 |
| Sample Rate | 6.43/sec |
| Health Score | 402% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 11 |
| Allocations | 436 |

<details>
<summary>CPU Timeline (3 unique values: 81-96 cores)</summary>

```
1791988943 81
1791988948 81
1791988953 81
1791988958 81
1791988963 86
1791988968 86
1791988973 96
1791988978 96
1791988983 96
1791988988 96
1791988993 96
1791988998 96
1791989003 96
1791989008 96
1791989013 96
1791989018 96
1791989023 96
1791989028 96
1791989033 96
1791989038 96
```
</details>

---

