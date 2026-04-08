---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-08 13:30:11 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 8 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1775668988 32
1775668993 32
1775668998 32
1775669003 30
1775669008 30
1775669013 32
1775669018 32
1775669023 32
1775669028 32
1775669033 32
1775669038 32
1775669043 32
1775669048 32
1775669053 32
1775669058 32
1775669063 32
1775669068 32
1775669073 32
1775669078 32
1775669083 32
```
</details>

---

