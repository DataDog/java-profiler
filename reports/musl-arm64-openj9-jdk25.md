---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-24 16:31:58 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 177 |
| Sample Rate | 2.95/sec |
| Health Score | 184% |
| Threads | 9 |
| Allocations | 161 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 6 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (3 unique values: 26-64 cores)</summary>

```
1790281527 27
1790281532 27
1790281537 27
1790281542 27
1790281547 27
1790281552 27
1790281557 27
1790281562 27
1790281567 26
1790281572 26
1790281577 26
1790281582 26
1790281587 26
1790281592 26
1790281597 26
1790281602 26
1790281607 26
1790281612 26
1790281617 26
1790281622 27
```
</details>

---

