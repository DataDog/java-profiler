---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-23 10:27:23 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 792 |
| Sample Rate | 13.20/sec |
| Health Score | 825% |
| Threads | 11 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (5 unique values: 76-96 cores)</summary>

```
1790173249 76
1790173254 76
1790173259 86
1790173264 86
1790173269 86
1790173274 96
1790173279 96
1790173284 94
1790173289 94
1790173294 92
1790173299 92
1790173304 92
1790173309 92
1790173314 92
1790173319 92
1790173324 92
1790173329 94
1790173334 94
1790173339 92
1790173344 92
```
</details>

---

