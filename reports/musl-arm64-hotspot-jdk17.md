---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-18 21:28:17 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 160 |
| Sample Rate | 2.67/sec |
| Health Score | 167% |
| Threads | 10 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792373018 48
1792373023 48
1792373028 43
1792373033 43
1792373038 43
1792373043 43
1792373048 43
1792373053 43
1792373058 43
1792373063 43
1792373068 43
1792373073 43
1792373078 43
1792373083 43
1792373088 48
1792373093 48
1792373098 48
1792373103 48
1792373108 48
1792373113 48
```
</details>

---

