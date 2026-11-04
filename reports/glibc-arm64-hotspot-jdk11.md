---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 09:07:14 EST

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
| CPU Cores (start) | 11 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 191 |
| Sample Rate | 3.18/sec |
| Health Score | 199% |
| Threads | 10 |
| Allocations | 138 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 7 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (3 unique values: 11-14 cores)</summary>

```
1793800935 11
1793800940 11
1793800945 11
1793800950 11
1793800955 11
1793800960 11
1793800965 11
1793800970 11
1793800975 11
1793800980 11
1793800985 14
1793800990 14
1793800995 12
1793801000 12
1793801005 12
1793801010 12
1793801015 12
1793801020 12
1793801025 12
1793801030 12
```
</details>

---

