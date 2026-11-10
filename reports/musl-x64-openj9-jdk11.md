---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 12:41:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 786 |
| Sample Rate | 13.10/sec |
| Health Score | 819% |
| Threads | 11 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (2 unique values: 44-46 cores)</summary>

```
1794331977 44
1794331982 44
1794331987 44
1794331992 44
1794331997 44
1794332002 44
1794332007 46
1794332012 46
1794332017 46
1794332022 46
1794332027 46
1794332032 46
1794332037 46
1794332042 46
1794332047 46
1794332052 46
1794332057 46
1794332062 46
1794332067 46
1794332072 46
```
</details>

---

