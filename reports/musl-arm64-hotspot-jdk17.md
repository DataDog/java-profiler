---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ❌ FAIL

**Date:** 2026-11-20 12:23:34 EST

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 13 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (1 unique values: 14-14 cores)</summary>

```
1795195140 14
1795195145 14
1795195150 14
1795195155 14
1795195160 14
1795195165 14
1795195170 14
1795195175 14
1795195180 14
1795195185 14
1795195190 14
1795195195 14
1795195200 14
1795195205 14
1795195210 14
1795195215 14
1795195220 14
1795195225 14
1795195230 14
1795195235 14
```
</details>

---

