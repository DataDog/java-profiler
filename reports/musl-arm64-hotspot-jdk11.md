---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-05 19:52:39 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 11 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 315 |
| Sample Rate | 5.25/sec |
| Health Score | 328% |
| Threads | 14 |
| Allocations | 134 |

<details>
<summary>CPU Timeline (3 unique values: 38-43 cores)</summary>

```
1793926081 38
1793926086 38
1793926091 38
1793926096 41
1793926101 41
1793926106 41
1793926111 41
1793926116 41
1793926121 43
1793926126 43
1793926131 41
1793926136 41
1793926141 41
1793926146 41
1793926151 41
1793926156 41
1793926161 41
1793926166 41
1793926171 43
1793926176 43
```
</details>

---

