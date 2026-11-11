---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 06:07:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 406 |
| Sample Rate | 6.77/sec |
| Health Score | 423% |
| Threads | 8 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 11 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (3 unique values: 16-22 cores)</summary>

```
1794395023 16
1794395028 16
1794395033 16
1794395038 16
1794395043 16
1794395048 16
1794395053 16
1794395058 16
1794395063 16
1794395068 16
1794395073 16
1794395078 17
1794395083 17
1794395088 17
1794395093 17
1794395098 17
1794395103 17
1794395108 17
1794395113 17
1794395118 17
```
</details>

---

