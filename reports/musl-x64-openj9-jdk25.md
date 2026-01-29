---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-01-29 06:14:26 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 18.83/sec |
| Health Score | 1177% |
| Threads | 11 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 904 |
| Sample Rate | 30.13/sec |
| Health Score | 1883% |
| Threads | 13 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (5 unique values: 79-88 cores)</summary>

```
1769685027 82
1769685032 82
1769685037 82
1769685042 82
1769685048 82
1769685053 82
1769685058 79
1769685063 79
1769685068 81
1769685073 81
1769685078 84
1769685083 84
1769685088 84
1769685093 88
1769685098 88
1769685103 88
1769685108 88
1769685113 88
1769685118 88
1769685123 88
```
</details>

---

