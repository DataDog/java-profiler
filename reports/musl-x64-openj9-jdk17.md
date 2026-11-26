---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-26 11:54:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 11 |
| Allocations | 86 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 7 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 44-72 cores)</summary>

```
1795711797 72
1795711802 72
1795711807 72
1795711812 72
1795711818 72
1795711823 72
1795711828 44
1795711833 44
1795711838 44
1795711843 44
1795711848 44
1795711853 44
1795711858 44
1795711863 44
1795711868 44
1795711873 44
1795711878 44
1795711883 44
1795711888 44
1795711893 44
```
</details>

---

