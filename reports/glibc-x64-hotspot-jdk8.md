---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-20 09:32:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 204 |
| Sample Rate | 3.40/sec |
| Health Score | 212% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 203 |
| Sample Rate | 3.38/sec |
| Health Score | 211% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 88-96 cores)</summary>

```
1787232407 96
1787232412 96
1787232417 96
1787232422 96
1787232427 96
1787232432 96
1787232437 96
1787232442 96
1787232447 96
1787232452 96
1787232457 96
1787232462 96
1787232467 96
1787232472 96
1787232477 96
1787232482 96
1787232487 88
1787232492 88
1787232497 88
1787232502 88
```
</details>

---

