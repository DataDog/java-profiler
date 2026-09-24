---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-24 16:31:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 874 |
| Sample Rate | 14.57/sec |
| Health Score | 911% |
| Threads | 10 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1790281519 32
1790281524 32
1790281529 32
1790281534 32
1790281539 32
1790281544 32
1790281549 32
1790281554 32
1790281559 32
1790281564 32
1790281569 32
1790281574 32
1790281579 32
1790281584 32
1790281589 32
1790281594 32
1790281599 32
1790281604 32
1790281609 32
1790281614 32
```
</details>

---

