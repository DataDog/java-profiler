---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-26 06:15:14 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 7 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795691149 64
1795691154 64
1795691159 64
1795691164 64
1795691169 64
1795691174 64
1795691180 64
1795691185 33
1795691190 33
1795691195 33
1795691200 33
1795691205 33
1795691210 33
1795691215 33
1795691220 33
1795691225 33
1795691230 33
1795691235 33
1795691240 33
1795691245 33
```
</details>

---

