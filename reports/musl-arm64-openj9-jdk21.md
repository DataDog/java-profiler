---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-01 14:34:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (3 unique values: 47-64 cores)</summary>

```
1788287376 64
1788287381 64
1788287386 64
1788287391 64
1788287396 64
1788287401 64
1788287406 52
1788287411 52
1788287416 52
1788287421 52
1788287426 52
1788287431 52
1788287436 47
1788287441 47
1788287446 47
1788287451 47
1788287456 47
1788287461 47
1788287466 47
1788287471 47
```
</details>

---

