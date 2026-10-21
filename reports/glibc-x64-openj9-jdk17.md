---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-21 05:55:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 11 |
| Allocations | 424 |

<details>
<summary>CPU Timeline (4 unique values: 71-96 cores)</summary>

```
1792576223 96
1792576228 96
1792576233 96
1792576238 96
1792576243 96
1792576248 96
1792576253 94
1792576258 94
1792576263 94
1792576268 94
1792576273 73
1792576278 73
1792576283 73
1792576288 73
1792576293 73
1792576298 73
1792576303 73
1792576308 73
1792576313 73
1792576318 73
```
</details>

---

