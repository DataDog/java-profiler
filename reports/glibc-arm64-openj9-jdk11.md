---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-14 10:47:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 11 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (3 unique values: 46-64 cores)</summary>

```
1791988923 46
1791988928 46
1791988933 46
1791988938 46
1791988943 46
1791988948 46
1791988953 46
1791988958 46
1791988963 46
1791988968 46
1791988973 46
1791988978 46
1791988983 46
1791988988 46
1791988993 51
1791988998 51
1791989003 51
1791989008 51
1791989013 64
1791989018 64
```
</details>

---

