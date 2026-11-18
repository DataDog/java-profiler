---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 00:06:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1794978125 29
1794978130 29
1794978135 29
1794978140 29
1794978145 29
1794978150 29
1794978155 29
1794978160 34
1794978165 34
1794978170 29
1794978175 29
1794978180 29
1794978185 29
1794978190 29
1794978195 29
1794978200 29
1794978205 29
1794978210 29
1794978215 29
1794978220 29
```
</details>

---

