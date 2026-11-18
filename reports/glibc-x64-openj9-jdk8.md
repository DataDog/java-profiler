---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-18 09:30:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 163 |
| Sample Rate | 2.72/sec |
| Health Score | 170% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 171 |
| Sample Rate | 2.85/sec |
| Health Score | 178% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 66-76 cores)</summary>

```
1795011965 76
1795011970 76
1795011975 76
1795011980 76
1795011985 74
1795011990 74
1795011995 74
1795012000 72
1795012005 72
1795012010 72
1795012015 72
1795012020 66
1795012025 66
1795012030 66
1795012035 66
1795012040 66
1795012045 66
1795012050 66
1795012055 68
1795012060 68
```
</details>

---

