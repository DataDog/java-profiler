---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-23 21:25:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 7 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 36 |
| Sample Rate | 0.60/sec |
| Health Score | 37% |
| Threads | 7 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787534407 64
1787534412 64
1787534417 64
1787534422 64
1787534427 64
1787534432 64
1787534437 64
1787534442 64
1787534447 64
1787534452 64
1787534457 64
1787534462 64
1787534467 64
1787534472 64
1787534477 64
1787534482 64
1787534487 64
1787534492 64
1787534497 64
1787534502 64
```
</details>

---

