---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-26 12:32:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 8 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 12 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (3 unique values: 35-42 cores)</summary>

```
1793032020 42
1793032025 42
1793032030 42
1793032035 42
1793032040 42
1793032045 42
1793032050 42
1793032055 42
1793032060 42
1793032065 42
1793032070 42
1793032075 42
1793032080 42
1793032085 42
1793032090 42
1793032095 42
1793032100 41
1793032105 41
1793032110 41
1793032115 41
```
</details>

---

