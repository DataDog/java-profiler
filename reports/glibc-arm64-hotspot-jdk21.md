---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-26 12:32:03 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 235 |
| Sample Rate | 3.92/sec |
| Health Score | 245% |
| Threads | 10 |
| Allocations | 179 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 7 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (2 unique values: 41-45 cores)</summary>

```
1793032040 41
1793032045 41
1793032050 41
1793032055 41
1793032060 41
1793032065 45
1793032070 45
1793032075 45
1793032080 45
1793032085 45
1793032090 45
1793032095 45
1793032100 45
1793032105 45
1793032110 45
1793032115 45
1793032120 45
1793032125 45
1793032130 45
1793032135 45
```
</details>

---

