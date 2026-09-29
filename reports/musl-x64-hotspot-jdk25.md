---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-29 08:24:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 12 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (3 unique values: 63-96 cores)</summary>

```
1790684404 79
1790684409 79
1790684414 79
1790684419 79
1790684424 79
1790684429 79
1790684434 79
1790684439 79
1790684444 79
1790684449 79
1790684454 79
1790684459 79
1790684464 96
1790684470 96
1790684475 63
1790684480 63
1790684485 63
1790684490 63
1790684495 63
1790684500 63
```
</details>

---

