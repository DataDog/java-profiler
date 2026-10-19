---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-18 21:28:18 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 45 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 277 |
| Sample Rate | 4.62/sec |
| Health Score | 289% |
| Threads | 12 |
| Allocations | 156 |

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

