---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-06 00:04:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 8 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 9 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (4 unique values: 43-60 cores)</summary>

```
1793941181 45
1793941186 45
1793941191 45
1793941196 45
1793941201 45
1793941206 43
1793941211 43
1793941216 43
1793941221 60
1793941226 60
1793941231 60
1793941236 60
1793941241 60
1793941246 60
1793941251 60
1793941256 60
1793941261 60
1793941266 60
1793941271 58
1793941276 58
```
</details>

---

