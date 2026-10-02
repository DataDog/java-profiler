---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-02 12:03:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1790956758 40
1790956763 40
1790956768 40
1790956773 40
1790956778 40
1790956783 40
1790956788 40
1790956793 40
1790956798 40
1790956803 40
1790956808 40
1790956813 40
1790956818 40
1790956823 40
1790956828 40
1790956833 40
1790956838 40
1790956843 40
1790956848 40
1790956853 40
```
</details>

---

