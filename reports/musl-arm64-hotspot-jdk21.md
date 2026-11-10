---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 18:14:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 315 |
| Sample Rate | 5.25/sec |
| Health Score | 328% |
| Threads | 10 |
| Allocations | 157 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 13 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1794352210 51
1794352215 51
1794352220 51
1794352225 51
1794352230 51
1794352236 51
1794352241 51
1794352246 51
1794352251 51
1794352256 51
1794352261 51
1794352266 51
1794352271 51
1794352276 51
1794352281 51
1794352286 51
1794352291 51
1794352296 51
1794352301 51
1794352306 64
```
</details>

---

