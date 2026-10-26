---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-26 06:57:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 724 |
| Sample Rate | 12.07/sec |
| Health Score | 754% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 870 |
| Sample Rate | 14.50/sec |
| Health Score | 906% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (3 unique values: 72-78 cores)</summary>

```
1793012015 72
1793012020 74
1793012025 74
1793012030 72
1793012035 72
1793012040 72
1793012045 72
1793012050 72
1793012055 72
1793012060 72
1793012065 72
1793012070 72
1793012075 72
1793012080 74
1793012085 74
1793012090 78
1793012095 78
1793012100 78
1793012105 78
1793012110 78
```
</details>

---

