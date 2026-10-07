---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-07 07:29:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 167 |
| Sample Rate | 2.78/sec |
| Health Score | 174% |
| Threads | 10 |
| Allocations | 157 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 7 |
| Sample Rate | 0.12/sec |
| Health Score | 8% |
| Threads | 6 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1791372319 40
1791372324 40
1791372329 40
1791372334 40
1791372339 40
1791372344 40
1791372349 40
1791372354 40
1791372359 40
1791372364 35
1791372369 35
1791372374 35
1791372379 35
1791372384 35
1791372389 35
1791372394 35
1791372399 35
1791372404 35
1791372409 35
1791372414 35
```
</details>

---

