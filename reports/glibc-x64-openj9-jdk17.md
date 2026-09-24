---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-24 16:31:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 761 |
| Sample Rate | 12.68/sec |
| Health Score | 792% |
| Threads | 9 |
| Allocations | 430 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1790281547 32
1790281552 32
1790281557 32
1790281562 32
1790281567 32
1790281572 32
1790281577 32
1790281582 32
1790281587 32
1790281592 32
1790281597 32
1790281602 32
1790281607 32
1790281612 32
1790281617 32
1790281622 32
1790281627 32
1790281632 32
1790281637 32
1790281642 32
```
</details>

---

