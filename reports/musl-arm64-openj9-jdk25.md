---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-21 00:47:26 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 8 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 10 |
| Allocations | 88 |

<details>
<summary>CPU Timeline (1 unique values: 49-49 cores)</summary>

```
1789965818 49
1789965823 49
1789965828 49
1789965833 49
1789965838 49
1789965843 49
1789965848 49
1789965853 49
1789965858 49
1789965863 49
1789965868 49
1789965873 49
1789965879 49
1789965884 49
1789965889 49
1789965894 49
1789965899 49
1789965904 49
1789965909 49
1789965914 49
```
</details>

---

