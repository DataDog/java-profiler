---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-06 11:23:39 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 417 |
| Sample Rate | 6.95/sec |
| Health Score | 434% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 10 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1791299929 32
1791299934 32
1791299939 32
1791299944 32
1791299949 32
1791299954 32
1791299959 32
1791299964 32
1791299969 32
1791299974 32
1791299979 32
1791299984 32
1791299989 32
1791299994 32
1791299999 32
1791300004 32
1791300009 32
1791300014 32
1791300019 32
1791300024 32
```
</details>

---

