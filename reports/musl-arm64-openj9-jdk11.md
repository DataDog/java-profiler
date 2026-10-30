---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-30 06:56:11 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 8 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 296 |
| Sample Rate | 4.93/sec |
| Health Score | 308% |
| Threads | 11 |
| Allocations | 140 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1793357474 47
1793357479 48
1793357484 48
1793357489 48
1793357494 48
1793357499 48
1793357504 48
1793357509 48
1793357514 48
1793357519 48
1793357524 48
1793357529 48
1793357534 48
1793357539 48
1793357544 48
1793357549 48
1793357554 48
1793357559 48
1793357564 48
1793357569 48
```
</details>

---

