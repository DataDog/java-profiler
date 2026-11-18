---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 10:25:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 10 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (2 unique values: 33-38 cores)</summary>

```
1795015325 38
1795015330 38
1795015335 38
1795015340 38
1795015345 38
1795015350 38
1795015355 38
1795015360 38
1795015365 38
1795015370 38
1795015375 38
1795015380 38
1795015385 38
1795015390 33
1795015395 33
1795015400 33
1795015405 33
1795015410 33
1795015415 33
1795015420 33
```
</details>

---

