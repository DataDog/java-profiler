---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-11 00:57:47 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 207 |
| Sample Rate | 3.45/sec |
| Health Score | 216% |
| Threads | 11 |
| Allocations | 153 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 14 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1786424047 59
1786424052 64
1786424057 64
1786424062 64
1786424067 64
1786424072 64
1786424077 64
1786424082 64
1786424087 64
1786424092 64
1786424097 64
1786424102 64
1786424107 64
1786424112 64
1786424117 64
1786424122 59
1786424127 59
1786424132 59
1786424137 59
1786424142 59
```
</details>

---

