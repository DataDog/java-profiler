---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-05 15:44:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 455 |
| Sample Rate | 7.58/sec |
| Health Score | 474% |
| Threads | 10 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 13 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1772743236 43
1772743241 43
1772743246 43
1772743251 43
1772743256 43
1772743261 43
1772743266 38
1772743271 38
1772743276 38
1772743281 38
1772743286 38
1772743291 38
1772743296 38
1772743301 38
1772743306 38
1772743311 38
1772743316 38
1772743321 38
1772743326 38
1772743331 38
```
</details>

---

