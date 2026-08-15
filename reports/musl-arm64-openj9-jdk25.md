---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-15 05:47:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 12 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1786787025 46
1786787030 46
1786787035 48
1786787040 48
1786787045 48
1786787050 48
1786787055 48
1786787060 48
1786787065 48
1786787070 48
1786787075 48
1786787080 48
1786787085 48
1786787090 48
1786787095 48
1786787100 48
1786787105 48
1786787110 48
1786787115 48
1786787120 48
```
</details>

---

