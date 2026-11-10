---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-10 05:58:43 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 10 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 12 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794307961 48
1794307966 48
1794307971 48
1794307976 48
1794307981 48
1794307987 48
1794307992 48
1794307997 48
1794308002 48
1794308007 48
1794308012 48
1794308017 48
1794308022 48
1794308027 48
1794308032 48
1794308037 48
1794308042 48
1794308047 48
1794308052 48
1794308057 48
```
</details>

---

