---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 13:41:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 12 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 263 |
| Sample Rate | 4.38/sec |
| Health Score | 274% |
| Threads | 14 |
| Allocations | 139 |

<details>
<summary>CPU Timeline (2 unique values: 45-50 cores)</summary>

```
1795199788 50
1795199793 50
1795199798 50
1795199803 50
1795199808 50
1795199813 50
1795199818 50
1795199823 50
1795199828 50
1795199833 50
1795199838 50
1795199843 50
1795199848 50
1795199853 45
1795199858 45
1795199863 45
1795199868 45
1795199873 45
1795199878 45
1795199883 45
```
</details>

---

