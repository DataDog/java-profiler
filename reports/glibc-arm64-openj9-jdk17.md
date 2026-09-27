---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-27 00:58:57 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 265 |
| Sample Rate | 4.42/sec |
| Health Score | 276% |
| Threads | 12 |
| Allocations | 84 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1790484798 64
1790484803 64
1790484808 64
1790484813 64
1790484818 64
1790484823 64
1790484828 64
1790484833 64
1790484838 64
1790484843 64
1790484848 64
1790484853 64
1790484858 64
1790484863 64
1790484868 64
1790484873 64
1790484878 64
1790484883 64
1790484888 64
1790484893 64
```
</details>

---

