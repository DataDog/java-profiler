---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 07:11:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 8 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 28 |
| Sample Rate | 0.47/sec |
| Health Score | 29% |
| Threads | 7 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795694813 64
1795694818 64
1795694823 64
1795694828 64
1795694833 64
1795694838 64
1795694843 64
1795694848 64
1795694853 64
1795694858 64
1795694863 64
1795694868 64
1795694873 64
1795694878 64
1795694883 64
1795694888 64
1795694893 64
1795694898 64
1795694903 64
1795694908 64
```
</details>

---

