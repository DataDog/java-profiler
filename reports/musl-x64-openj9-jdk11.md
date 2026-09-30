---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 07:31:56 EDT

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 732 |
| Sample Rate | 12.20/sec |
| Health Score | 762% |
| Threads | 10 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (3 unique values: 57-75 cores)</summary>

```
1790767612 57
1790767617 57
1790767622 57
1790767627 57
1790767632 57
1790767637 57
1790767642 57
1790767647 57
1790767652 65
1790767657 65
1790767662 65
1790767667 65
1790767672 65
1790767677 65
1790767682 75
1790767687 75
1790767692 75
1790767697 75
1790767702 75
1790767707 75
```
</details>

---

