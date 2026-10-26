---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-26 07:41:00 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 216 |
| Sample Rate | 3.60/sec |
| Health Score | 225% |
| Threads | 10 |
| Allocations | 159 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 13 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1793014542 51
1793014547 51
1793014552 51
1793014557 51
1793014562 51
1793014567 51
1793014572 51
1793014577 51
1793014582 51
1793014587 51
1793014592 51
1793014597 51
1793014602 51
1793014607 49
1793014612 49
1793014617 49
1793014622 49
1793014627 49
1793014632 49
1793014637 49
```
</details>

---

