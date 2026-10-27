---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-27 07:43:59 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 10 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (2 unique values: 56-64 cores)</summary>

```
1793101189 64
1793101195 64
1793101200 64
1793101205 64
1793101210 64
1793101215 64
1793101220 64
1793101225 64
1793101230 64
1793101235 64
1793101240 64
1793101245 64
1793101250 64
1793101255 56
1793101260 56
1793101265 56
1793101270 56
1793101275 56
1793101280 56
1793101285 56
```
</details>

---

