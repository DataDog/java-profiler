---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-10 12:21:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 9 |
| Allocations | 425 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 750 |
| Sample Rate | 12.50/sec |
| Health Score | 781% |
| Threads | 10 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (2 unique values: 71-79 cores)</summary>

```
1794331027 79
1794331032 79
1794331037 79
1794331042 79
1794331047 79
1794331052 79
1794331057 79
1794331062 79
1794331067 79
1794331072 79
1794331077 71
1794331082 71
1794331087 71
1794331092 71
1794331097 71
1794331102 71
1794331107 71
1794331112 71
1794331117 71
1794331122 71
```
</details>

---

