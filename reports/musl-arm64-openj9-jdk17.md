---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 06:56:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 9 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (2 unique values: 28-44 cores)</summary>

```
1795434714 44
1795434719 44
1795434724 44
1795434729 28
1795434734 28
1795434739 28
1795434744 28
1795434749 28
1795434754 28
1795434759 28
1795434764 28
1795434769 28
1795434774 28
1795434779 28
1795434784 28
1795434790 28
1795434795 28
1795434800 28
1795434805 28
1795434810 28
```
</details>

---

