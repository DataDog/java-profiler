---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 08:02:18 EST

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 10 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (4 unique values: 88-94 cores)</summary>

```
1795093073 90
1795093078 90
1795093083 90
1795093088 90
1795093093 88
1795093098 88
1795093103 88
1795093108 88
1795093113 88
1795093118 88
1795093123 88
1795093128 90
1795093133 90
1795093138 90
1795093143 88
1795093148 88
1795093153 88
1795093158 88
1795093163 88
1795093168 88
```
</details>

---

