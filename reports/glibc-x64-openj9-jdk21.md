---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 08:02:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 9 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 708 |
| Sample Rate | 11.80/sec |
| Health Score | 738% |
| Threads | 10 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (3 unique values: 89-93 cores)</summary>

```
1794488229 91
1794488234 91
1794488239 91
1794488244 91
1794488249 91
1794488254 91
1794488259 91
1794488264 91
1794488269 89
1794488274 89
1794488279 89
1794488284 89
1794488289 91
1794488294 91
1794488299 93
1794488304 93
1794488309 93
1794488314 93
1794488319 93
1794488324 93
```
</details>

---

