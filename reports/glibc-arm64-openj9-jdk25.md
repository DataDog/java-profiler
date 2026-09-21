---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-21 09:40:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 193 |
| Sample Rate | 3.22/sec |
| Health Score | 201% |
| Threads | 12 |
| Allocations | 194 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 11 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (3 unique values: 35-49 cores)</summary>

```
1789997748 35
1789997753 35
1789997758 35
1789997763 35
1789997768 35
1789997773 35
1789997778 35
1789997783 35
1789997788 35
1789997793 40
1789997798 40
1789997803 40
1789997808 40
1789997813 49
1789997818 49
1789997823 49
1789997828 49
1789997833 49
1789997838 49
1789997843 49
```
</details>

---

