---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 11:34:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 12 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1790090974 48
1790090979 48
1790090984 48
1790090989 48
1790090994 48
1790090999 48
1790091004 48
1790091009 48
1790091014 48
1790091019 48
1790091024 48
1790091029 48
1790091034 48
1790091039 48
1790091044 48
1790091049 48
1790091054 36
1790091059 36
1790091064 36
1790091069 36
```
</details>

---

