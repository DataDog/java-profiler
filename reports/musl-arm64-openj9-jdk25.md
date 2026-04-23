---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-23 16:30:52 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 13 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776975924 64
1776975929 64
1776975934 64
1776975939 64
1776975944 64
1776975949 64
1776975954 64
1776975959 64
1776975964 64
1776975969 64
1776975974 64
1776975979 64
1776975984 64
1776975989 64
1776975994 64
1776975999 64
1776976004 64
1776976009 64
1776976014 64
1776976019 64
```
</details>

---

