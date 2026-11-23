---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 06:56:59 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 127 |
| Sample Rate | 2.12/sec |
| Health Score | 132% |
| Threads | 11 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (3 unique values: 48-64 cores)</summary>

```
1795434724 49
1795434729 49
1795434734 49
1795434739 49
1795434744 49
1795434749 49
1795434754 49
1795434759 49
1795434764 49
1795434769 49
1795434774 49
1795434779 64
1795434784 64
1795434789 64
1795434794 64
1795434799 64
1795434804 64
1795434809 64
1795434814 64
1795434819 64
```
</details>

---

