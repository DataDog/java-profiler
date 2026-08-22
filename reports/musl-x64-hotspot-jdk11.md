---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-22 09:23:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 758 |
| Sample Rate | 12.63/sec |
| Health Score | 789% |
| Threads | 9 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (3 unique values: 21-61 cores)</summary>

```
1787404767 61
1787404772 61
1787404777 61
1787404782 61
1787404787 61
1787404792 61
1787404797 61
1787404802 61
1787404807 61
1787404812 61
1787404817 61
1787404822 61
1787404827 61
1787404832 61
1787404837 41
1787404842 41
1787404847 41
1787404852 41
1787404857 21
1787404862 21
```
</details>

---

