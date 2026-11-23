---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-22 20:31:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 192 |
| Sample Rate | 3.20/sec |
| Health Score | 200% |
| Threads | 11 |
| Allocations | 174 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 10 |
| Allocations | 51 |

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

