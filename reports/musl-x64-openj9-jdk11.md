---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-30 10:12:30 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 848 |
| Sample Rate | 14.13/sec |
| Health Score | 883% |
| Threads | 10 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (8 unique values: 52-78 cores)</summary>

```
1777558053 52
1777558058 52
1777558063 52
1777558068 57
1777558073 57
1777558078 57
1777558083 61
1777558088 61
1777558093 65
1777558098 65
1777558103 65
1777558108 63
1777558113 63
1777558119 63
1777558124 64
1777558129 64
1777558134 66
1777558139 66
1777558144 78
1777558149 78
```
</details>

---

