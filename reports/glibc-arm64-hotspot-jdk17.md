---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-23 06:16:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 282 |
| Sample Rate | 4.70/sec |
| Health Score | 294% |
| Threads | 11 |
| Allocations | 101 |

<details>
<summary>CPU Timeline (2 unique values: 44-49 cores)</summary>

```
1795432110 49
1795432115 49
1795432120 49
1795432125 49
1795432130 49
1795432135 49
1795432140 49
1795432145 49
1795432150 49
1795432155 49
1795432160 49
1795432165 49
1795432170 49
1795432175 44
1795432180 44
1795432185 44
1795432190 44
1795432195 44
1795432200 44
1795432205 44
```
</details>

---

