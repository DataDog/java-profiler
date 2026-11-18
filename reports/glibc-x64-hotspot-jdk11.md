---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 10:28:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 732 |
| Sample Rate | 12.20/sec |
| Health Score | 762% |
| Threads | 10 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (3 unique values: 42-46 cores)</summary>

```
1795015382 44
1795015387 44
1795015392 44
1795015397 44
1795015402 44
1795015407 44
1795015412 44
1795015417 44
1795015422 44
1795015427 42
1795015432 42
1795015437 42
1795015442 42
1795015447 42
1795015452 42
1795015457 42
1795015462 42
1795015467 42
1795015472 42
1795015477 42
```
</details>

---

