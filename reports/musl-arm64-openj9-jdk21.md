---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-19 11:59:39 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 10 |
| Allocations | 86 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 15 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (2 unique values: 41-46 cores)</summary>

```
1787154918 41
1787154923 41
1787154928 46
1787154933 46
1787154938 46
1787154943 46
1787154948 46
1787154953 46
1787154958 46
1787154964 46
1787154969 46
1787154974 46
1787154979 46
1787154984 46
1787154989 46
1787154994 46
1787154999 46
1787155004 46
1787155009 46
1787155014 46
```
</details>

---

