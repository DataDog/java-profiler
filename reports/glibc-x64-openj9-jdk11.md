---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 06:09:24 EST

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 134 |
| Sample Rate | 2.23/sec |
| Health Score | 139% |
| Threads | 9 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 5 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (5 unique values: 68-94 cores)</summary>

```
1795691105 85
1795691110 85
1795691115 85
1795691120 85
1795691125 85
1795691130 85
1795691135 85
1795691140 85
1795691145 85
1795691150 94
1795691155 94
1795691160 94
1795691165 94
1795691170 94
1795691175 94
1795691180 94
1795691185 94
1795691190 91
1795691195 91
1795691200 68
```
</details>

---

