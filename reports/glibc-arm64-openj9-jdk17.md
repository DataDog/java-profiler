---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-20 13:41:31 EST

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
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 11 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 12 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795199783 64
1795199788 64
1795199793 64
1795199798 64
1795199803 64
1795199808 64
1795199813 64
1795199818 64
1795199823 64
1795199828 64
1795199833 64
1795199838 64
1795199843 64
1795199848 64
1795199853 64
1795199858 64
1795199863 64
1795199868 64
1795199873 64
1795199878 64
```
</details>

---

