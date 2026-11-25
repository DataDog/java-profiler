---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 06:18:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 8 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 778 |
| Sample Rate | 12.97/sec |
| Health Score | 811% |
| Threads | 11 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (2 unique values: 28-33 cores)</summary>

```
1795605035 33
1795605040 33
1795605045 33
1795605050 33
1795605055 33
1795605060 33
1795605065 33
1795605070 33
1795605075 33
1795605080 33
1795605085 33
1795605090 33
1795605095 33
1795605100 33
1795605105 33
1795605110 28
1795605115 28
1795605120 28
1795605125 28
1795605130 28
```
</details>

---

