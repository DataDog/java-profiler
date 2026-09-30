---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-30 07:31:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 8 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 787 |
| Sample Rate | 13.12/sec |
| Health Score | 820% |
| Threads | 10 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (4 unique values: 34-40 cores)</summary>

```
1790767622 36
1790767627 36
1790767632 34
1790767637 34
1790767642 36
1790767647 36
1790767652 38
1790767657 38
1790767662 38
1790767667 38
1790767672 38
1790767677 38
1790767682 38
1790767687 38
1790767692 38
1790767697 40
1790767702 40
1790767707 40
1790767712 40
1790767717 40
```
</details>

---

