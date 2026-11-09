---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-09 09:57:14 EST

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 413 |
| Sample Rate | 6.88/sec |
| Health Score | 430% |
| Threads | 9 |
| Allocations | 424 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 12 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (3 unique values: 35-40 cores)</summary>

```
1794235929 35
1794235934 35
1794235939 40
1794235944 40
1794235949 40
1794235954 40
1794235959 35
1794235964 35
1794235969 35
1794235974 35
1794235979 35
1794235984 35
1794235989 35
1794235994 35
1794235999 35
1794236004 35
1794236009 35
1794236014 40
1794236019 40
1794236024 38
```
</details>

---

