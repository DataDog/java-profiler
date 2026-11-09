---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-09 17:13:59 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 463 |
| Sample Rate | 7.72/sec |
| Health Score | 482% |
| Threads | 9 |
| Allocations | 326 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 12 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (4 unique values: 41-75 cores)</summary>

```
1794262134 56
1794262139 56
1794262144 56
1794262149 73
1794262154 73
1794262159 73
1794262164 73
1794262169 73
1794262174 73
1794262179 75
1794262184 75
1794262189 75
1794262194 75
1794262199 75
1794262204 75
1794262209 75
1794262214 75
1794262219 75
1794262224 75
1794262229 75
```
</details>

---

