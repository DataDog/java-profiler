---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-22 13:10:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 9 |
| Allocations | 93 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 15 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790096714 50
1790096719 50
1790096724 50
1790096729 50
1790096734 50
1790096739 50
1790096744 50
1790096749 50
1790096754 50
1790096759 50
1790096764 50
1790096769 50
1790096774 50
1790096779 50
1790096784 50
1790096789 50
1790096794 50
1790096799 50
1790096804 50
1790096809 50
```
</details>

---

