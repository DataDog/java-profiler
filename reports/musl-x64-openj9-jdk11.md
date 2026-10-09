---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-09 01:05:35 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 8 |
| Allocations | 436 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 10 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (4 unique values: 30-70 cores)</summary>

```
1791522003 30
1791522008 30
1791522013 30
1791522018 30
1791522023 70
1791522028 70
1791522033 70
1791522038 70
1791522043 49
1791522048 49
1791522053 49
1791522058 49
1791522063 49
1791522068 49
1791522073 49
1791522078 51
1791522083 51
1791522088 51
1791522093 51
1791522098 51
```
</details>

---

