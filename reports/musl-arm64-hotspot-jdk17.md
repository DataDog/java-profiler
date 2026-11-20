---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 09:53:29 EST

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 8 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 10 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (5 unique values: 41-46 cores)</summary>

```
1795186115 41
1795186120 41
1795186125 41
1795186130 41
1795186135 41
1795186140 41
1795186145 41
1795186150 41
1795186155 44
1795186160 44
1795186165 45
1795186170 45
1795186175 45
1795186180 45
1795186185 45
1795186190 45
1795186195 43
1795186200 43
1795186205 46
1795186210 46
```
</details>

---

