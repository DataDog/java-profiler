---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-17 14:55:34 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 12 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 11 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1794944990 64
1794944995 64
1794945000 64
1794945005 64
1794945010 64
1794945015 64
1794945020 64
1794945025 64
1794945030 64
1794945035 64
1794945040 64
1794945045 64
1794945050 64
1794945055 64
1794945060 64
1794945065 64
1794945070 64
1794945075 64
1794945080 64
1794945085 59
```
</details>

---

