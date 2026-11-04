---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 05:47:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 334 |
| Sample Rate | 5.57/sec |
| Health Score | 348% |
| Threads | 13 |
| Allocations | 124 |

<details>
<summary>CPU Timeline (1 unique values: 36-36 cores)</summary>

```
1793789061 36
1793789066 36
1793789071 36
1793789076 36
1793789081 36
1793789086 36
1793789091 36
1793789096 36
1793789101 36
1793789106 36
1793789111 36
1793789116 36
1793789121 36
1793789126 36
1793789131 36
1793789136 36
1793789141 36
1793789146 36
1793789151 36
1793789156 36
```
</details>

---

