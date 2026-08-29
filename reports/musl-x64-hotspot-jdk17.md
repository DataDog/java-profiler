---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-29 00:58:59 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 813 |
| Sample Rate | 13.55/sec |
| Health Score | 847% |
| Threads | 10 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (4 unique values: 60-66 cores)</summary>

```
1787979230 66
1787979235 66
1787979241 66
1787979246 66
1787979251 66
1787979256 66
1787979261 66
1787979266 64
1787979271 64
1787979276 62
1787979281 62
1787979286 60
1787979291 60
1787979296 60
1787979301 60
1787979306 60
1787979311 60
1787979316 60
1787979321 60
1787979326 60
```
</details>

---

