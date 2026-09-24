---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-24 04:39:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
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
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 14 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (3 unique values: 44-48 cores)</summary>

```
1790238970 44
1790238975 44
1790238980 44
1790238985 44
1790238990 44
1790238995 46
1790239000 46
1790239005 46
1790239010 46
1790239016 46
1790239021 46
1790239026 46
1790239031 46
1790239036 48
1790239041 48
1790239046 48
1790239051 48
1790239056 48
1790239061 48
1790239066 48
```
</details>

---

