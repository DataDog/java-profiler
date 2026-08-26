---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-26 15:31:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 818 |
| Sample Rate | 13.63/sec |
| Health Score | 852% |
| Threads | 10 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (3 unique values: 84-96 cores)</summary>

```
1787772342 84
1787772347 84
1787772352 84
1787772357 86
1787772362 86
1787772367 86
1787772372 86
1787772377 86
1787772382 86
1787772387 86
1787772392 86
1787772397 86
1787772402 86
1787772407 86
1787772412 86
1787772417 96
1787772422 96
1787772427 96
1787772432 96
1787772437 96
```
</details>

---

