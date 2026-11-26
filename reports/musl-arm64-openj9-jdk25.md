---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-26 06:09:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 9 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (6 unique values: 31-41 cores)</summary>

```
1795691085 34
1795691090 34
1795691095 34
1795691100 34
1795691105 34
1795691110 34
1795691115 34
1795691120 39
1795691125 39
1795691130 41
1795691135 41
1795691140 36
1795691145 36
1795691150 36
1795691155 36
1795691160 36
1795691165 36
1795691171 36
1795691176 36
1795691181 33
```
</details>

---

