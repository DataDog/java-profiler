---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-06 00:04:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 10 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 247 |
| Sample Rate | 4.12/sec |
| Health Score | 258% |
| Threads | 15 |
| Allocations | 156 |

<details>
<summary>CPU Timeline (3 unique values: 21-27 cores)</summary>

```
1793941221 27
1793941226 27
1793941231 27
1793941236 27
1793941241 27
1793941246 27
1793941251 22
1793941256 22
1793941261 22
1793941266 22
1793941271 22
1793941276 22
1793941281 22
1793941286 22
1793941291 22
1793941296 22
1793941301 22
1793941306 22
1793941311 27
1793941316 27
```
</details>

---

