---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-03-13 05:44:29 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 853 |
| Sample Rate | 14.22/sec |
| Health Score | 889% |
| Threads | 9 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (4 unique values: 38-45 cores)</summary>

```
1773394739 45
1773394744 45
1773394749 45
1773394754 45
1773394759 45
1773394764 45
1773394769 45
1773394774 45
1773394779 43
1773394784 43
1773394789 43
1773394794 43
1773394799 43
1773394804 43
1773394809 40
1773394814 40
1773394819 40
1773394824 40
1773394829 40
1773394834 40
```
</details>

---

