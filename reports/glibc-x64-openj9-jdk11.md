---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-27 17:32:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 770 |
| Sample Rate | 12.83/sec |
| Health Score | 802% |
| Threads | 9 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (3 unique values: 57-62 cores)</summary>

```
1777325192 62
1777325197 62
1777325202 57
1777325207 57
1777325212 57
1777325217 57
1777325222 57
1777325227 57
1777325232 57
1777325237 57
1777325242 57
1777325248 57
1777325253 60
1777325258 60
1777325263 60
1777325268 60
1777325273 60
1777325278 60
1777325283 60
1777325288 60
```
</details>

---

