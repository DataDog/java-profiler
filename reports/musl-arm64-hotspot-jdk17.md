---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-26 12:32:05 EDT

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
| CPU Cores (start) | 21 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 13 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (3 unique values: 21-26 cores)</summary>

```
1793031970 21
1793031975 21
1793031980 21
1793031985 21
1793031990 21
1793031995 21
1793032000 21
1793032005 21
1793032010 24
1793032015 24
1793032020 24
1793032025 24
1793032030 24
1793032035 24
1793032040 24
1793032045 26
1793032050 26
1793032055 26
1793032060 26
1793032065 26
```
</details>

---

