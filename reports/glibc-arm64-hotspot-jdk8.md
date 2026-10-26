---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-26 12:32:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 337 |
| Sample Rate | 5.62/sec |
| Health Score | 351% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 40 |
| Sample Rate | 0.67/sec |
| Health Score | 42% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1793032030 48
1793032035 48
1793032040 48
1793032045 48
1793032050 48
1793032055 48
1793032060 48
1793032065 48
1793032070 48
1793032075 48
1793032080 48
1793032085 48
1793032090 36
1793032095 36
1793032100 36
1793032105 36
1793032110 36
1793032115 36
1793032120 36
1793032125 36
```
</details>

---

