---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 13:41:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
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
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 342 |
| Sample Rate | 5.70/sec |
| Health Score | 356% |
| Threads | 11 |
| Allocations | 135 |

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

