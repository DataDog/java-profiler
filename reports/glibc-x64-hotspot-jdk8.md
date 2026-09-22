---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-22 13:10:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 155 |
| Sample Rate | 2.58/sec |
| Health Score | 161% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 37-42 cores)</summary>

```
1790096739 37
1790096744 37
1790096749 37
1790096754 37
1790096759 37
1790096764 37
1790096769 37
1790096774 37
1790096779 37
1790096784 37
1790096789 37
1790096794 42
1790096799 42
1790096804 42
1790096809 42
1790096814 42
1790096819 42
1790096824 42
1790096829 42
1790096834 42
```
</details>

---

