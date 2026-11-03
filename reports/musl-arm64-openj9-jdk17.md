---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-03 12:55:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 8 |
| CPU Cores (end) | 8 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 14 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (1 unique values: 8-8 cores)</summary>

```
1793728226 8
1793728231 8
1793728236 8
1793728241 8
1793728246 8
1793728251 8
1793728256 8
1793728261 8
1793728266 8
1793728271 8
1793728276 8
1793728281 8
1793728286 8
1793728291 8
1793728296 8
1793728301 8
1793728306 8
1793728311 8
1793728316 8
1793728321 8
```
</details>

---

