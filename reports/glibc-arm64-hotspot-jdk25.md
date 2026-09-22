---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-22 12:22:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
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
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 8 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790093774 50
1790093779 50
1790093784 50
1790093789 50
1790093794 50
1790093799 50
1790093804 50
1790093809 50
1790093814 50
1790093819 50
1790093824 50
1790093829 50
1790093834 50
1790093839 50
1790093844 50
1790093849 50
1790093854 50
1790093859 50
1790093864 50
1790093869 50
```
</details>

---

