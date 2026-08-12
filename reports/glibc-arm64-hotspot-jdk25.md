---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-12 05:20:30 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 10 |
| Allocations | 43 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 11 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1786526129 49
1786526135 49
1786526140 49
1786526145 49
1786526150 49
1786526155 49
1786526160 49
1786526165 49
1786526170 49
1786526175 49
1786526180 49
1786526185 49
1786526190 49
1786526195 49
1786526200 49
1786526205 49
1786526210 49
1786526215 51
1786526220 51
1786526225 51
```
</details>

---

