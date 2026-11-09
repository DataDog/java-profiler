---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-09 12:24:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 12 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 8 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794244753 43
1794244758 43
1794244763 43
1794244768 43
1794244773 43
1794244778 43
1794244783 43
1794244788 43
1794244793 43
1794244798 43
1794244803 43
1794244808 43
1794244813 43
1794244818 48
1794244823 48
1794244828 48
1794244833 48
1794244838 48
1794244843 48
1794244848 48
```
</details>

---

