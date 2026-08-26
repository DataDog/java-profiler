---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-26 15:31:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 10 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (4 unique values: 65-91 cores)</summary>

```
1787772347 91
1787772352 91
1787772357 91
1787772362 91
1787772367 91
1787772372 91
1787772377 91
1787772382 89
1787772387 89
1787772392 89
1787772397 89
1787772402 89
1787772407 89
1787772412 89
1787772417 89
1787772422 81
1787772427 81
1787772432 81
1787772437 81
1787772442 81
```
</details>

---

