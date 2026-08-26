---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-26 15:31:01 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 8 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 777 |
| Sample Rate | 12.95/sec |
| Health Score | 809% |
| Threads | 10 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1787772362 96
1787772367 96
1787772372 96
1787772377 96
1787772382 94
1787772387 94
1787772392 94
1787772397 94
1787772402 94
1787772407 94
1787772412 94
1787772417 94
1787772422 94
1787772427 94
1787772432 94
1787772437 94
1787772442 94
1787772447 94
1787772453 94
1787772458 94
```
</details>

---

