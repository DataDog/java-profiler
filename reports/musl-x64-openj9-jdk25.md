---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 12:00:55 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 10 |
| Allocations | 331 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 940 |
| Sample Rate | 15.67/sec |
| Health Score | 979% |
| Threads | 11 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (2 unique values: 83-87 cores)</summary>

```
1795452911 87
1795452916 87
1795452921 87
1795452926 87
1795452931 87
1795452936 87
1795452941 87
1795452946 87
1795452951 87
1795452957 87
1795452962 87
1795452967 87
1795452972 87
1795452977 87
1795452982 87
1795452987 83
1795452992 83
1795452997 83
1795453002 83
1795453007 83
```
</details>

---

