---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-09 06:10:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 8 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 11 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (3 unique values: 32-37 cores)</summary>

```
1791540273 34
1791540278 34
1791540283 34
1791540288 34
1791540293 34
1791540298 34
1791540303 37
1791540308 37
1791540313 37
1791540318 37
1791540323 37
1791540328 37
1791540333 37
1791540338 37
1791540343 37
1791540348 37
1791540353 37
1791540358 37
1791540364 37
1791540369 37
```
</details>

---

