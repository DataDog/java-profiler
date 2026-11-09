---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-09 18:48:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 8 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 8 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (2 unique values: 8-17 cores)</summary>

```
1794267782 17
1794267787 17
1794267792 17
1794267797 17
1794267802 17
1794267807 17
1794267812 8
1794267818 8
1794267823 8
1794267828 8
1794267833 8
1794267838 8
1794267843 8
1794267848 8
1794267853 8
1794267858 8
1794267863 8
1794267868 8
1794267873 8
1794267878 8
```
</details>

---

