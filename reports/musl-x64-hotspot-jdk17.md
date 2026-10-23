---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-23 05:58:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 10 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (2 unique values: 54-56 cores)</summary>

```
1792749129 56
1792749134 56
1792749139 56
1792749144 54
1792749149 54
1792749154 54
1792749159 54
1792749164 54
1792749169 54
1792749174 54
1792749179 54
1792749184 56
1792749189 56
1792749194 56
1792749199 56
1792749204 56
1792749209 56
1792749214 56
1792749219 56
1792749224 56
```
</details>

---

