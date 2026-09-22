---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-22 11:34:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790090938 43
1790090943 48
1790090948 48
1790090953 48
1790090958 48
1790090963 48
1790090968 48
1790090973 48
1790090978 48
1790090983 48
1790090988 48
1790090993 48
1790090998 48
1790091003 48
1790091008 48
1790091013 48
1790091018 48
1790091023 48
1790091028 48
1790091033 48
```
</details>

---

