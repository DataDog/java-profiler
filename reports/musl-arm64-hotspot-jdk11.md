---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 09:07:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 11 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 136 |
| Sample Rate | 2.27/sec |
| Health Score | 142% |
| Threads | 11 |
| Allocations | 27 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1793800910 34
1793800915 34
1793800920 34
1793800925 29
1793800930 29
1793800935 29
1793800940 29
1793800945 29
1793800950 29
1793800955 29
1793800960 29
1793800965 29
1793800970 29
1793800975 29
1793800980 29
1793800985 29
1793800990 29
1793800995 29
1793801000 29
1793801005 29
```
</details>

---

