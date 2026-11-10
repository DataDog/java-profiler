---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-10 14:54:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 10 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (2 unique values: 91-93 cores)</summary>

```
1794340119 93
1794340124 93
1794340129 93
1794340134 93
1794340139 93
1794340144 93
1794340149 93
1794340154 93
1794340159 93
1794340164 93
1794340169 93
1794340174 93
1794340179 91
1794340184 91
1794340189 91
1794340194 91
1794340199 91
1794340204 91
1794340209 91
1794340214 91
```
</details>

---

