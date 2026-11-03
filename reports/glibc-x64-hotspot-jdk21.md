---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-03 12:55:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 11 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (4 unique values: 90-96 cores)</summary>

```
1793728241 90
1793728246 90
1793728251 92
1793728256 92
1793728261 92
1793728266 92
1793728271 92
1793728276 92
1793728281 92
1793728286 92
1793728291 92
1793728296 92
1793728301 92
1793728306 92
1793728311 94
1793728316 94
1793728321 94
1793728326 94
1793728331 94
1793728336 94
```
</details>

---

