---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-24 04:39:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 394 |
| Sample Rate | 6.57/sec |
| Health Score | 411% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 14 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (3 unique values: 37-64 cores)</summary>

```
1790238950 64
1790238955 64
1790238960 64
1790238965 64
1790238970 64
1790238975 64
1790238980 64
1790238985 64
1790238990 64
1790238995 64
1790239000 64
1790239005 64
1790239010 64
1790239015 64
1790239020 57
1790239025 57
1790239030 57
1790239035 57
1790239040 37
1790239045 37
```
</details>

---

