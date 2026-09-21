---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-21 09:40:54 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 10 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (3 unique values: 22-49 cores)</summary>

```
1789997763 22
1789997768 22
1789997773 22
1789997778 22
1789997783 22
1789997788 22
1789997793 22
1789997798 22
1789997803 31
1789997808 31
1789997813 31
1789997818 31
1789997823 31
1789997828 31
1789997833 31
1789997838 49
1789997843 49
1789997848 49
1789997853 49
1789997858 49
```
</details>

---

