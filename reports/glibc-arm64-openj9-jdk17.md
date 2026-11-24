---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-24 05:51:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 305 |
| Sample Rate | 5.08/sec |
| Health Score | 318% |
| Threads | 12 |
| Allocations | 148 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 360 |
| Sample Rate | 6.00/sec |
| Health Score | 375% |
| Threads | 12 |
| Allocations | 130 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795517185 34
1795517190 34
1795517195 34
1795517200 34
1795517205 29
1795517210 29
1795517215 29
1795517220 29
1795517225 29
1795517230 29
1795517235 29
1795517240 29
1795517245 29
1795517250 29
1795517255 29
1795517260 29
1795517265 29
1795517271 29
1795517276 29
1795517281 29
```
</details>

---

