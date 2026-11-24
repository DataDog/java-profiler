---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-24 05:51:08 EST

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 9 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 11 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (3 unique values: 33-35 cores)</summary>

```
1795517185 35
1795517190 35
1795517195 35
1795517200 35
1795517205 35
1795517210 33
1795517215 33
1795517220 33
1795517225 33
1795517230 33
1795517235 33
1795517240 33
1795517245 33
1795517250 33
1795517255 33
1795517260 33
1795517265 33
1795517270 33
1795517275 33
1795517280 33
```
</details>

---

