---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 09:30:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 223 |
| Sample Rate | 3.72/sec |
| Health Score | 233% |
| Threads | 10 |
| Allocations | 138 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 14 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1795011975 46
1795011980 46
1795011985 46
1795011990 51
1795011995 51
1795012000 51
1795012005 51
1795012010 51
1795012015 51
1795012020 51
1795012025 51
1795012030 51
1795012035 51
1795012040 51
1795012045 51
1795012050 51
1795012055 51
1795012060 51
1795012065 51
1795012070 51
```
</details>

---

