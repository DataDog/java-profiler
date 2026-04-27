---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-27 16:29:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 281 |
| Sample Rate | 4.68/sec |
| Health Score | 292% |
| Threads | 14 |
| Allocations | 137 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1777321165 60
1777321170 60
1777321175 60
1777321180 60
1777321185 60
1777321190 60
1777321195 60
1777321200 60
1777321205 60
1777321210 60
1777321215 60
1777321220 64
1777321225 64
1777321230 64
1777321235 64
1777321240 64
1777321245 64
1777321250 64
1777321255 64
1777321260 64
```
</details>

---

