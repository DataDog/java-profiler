---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-22 20:31:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 9 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 12 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (3 unique values: 29-34 cores)</summary>

```
1795397210 29
1795397215 29
1795397220 29
1795397225 29
1795397230 29
1795397235 29
1795397240 29
1795397245 34
1795397250 34
1795397255 34
1795397260 34
1795397265 34
1795397270 34
1795397275 31
1795397280 31
1795397285 31
1795397290 31
1795397295 31
1795397300 31
1795397305 31
```
</details>

---

