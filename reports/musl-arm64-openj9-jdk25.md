---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-30 08:17:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 726 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 10 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (1 unique values: 42-42 cores)</summary>

```
1793362362 42
1793362367 42
1793362372 42
1793362377 42
1793362382 42
1793362387 42
1793362392 42
1793362397 42
1793362402 42
1793362407 42
1793362412 42
1793362417 42
1793362422 42
1793362427 42
1793362432 42
1793362437 42
1793362442 42
1793362447 42
1793362452 42
1793362457 42
```
</details>

---

