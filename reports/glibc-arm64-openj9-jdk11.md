---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-08 13:24:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 9 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (2 unique values: 11-16 cores)</summary>

```
1794162047 16
1794162052 16
1794162057 16
1794162062 16
1794162067 16
1794162072 16
1794162077 11
1794162082 11
1794162087 11
1794162092 11
1794162097 11
1794162102 11
1794162107 11
1794162112 11
1794162117 16
1794162122 16
1794162127 16
1794162132 16
1794162137 16
1794162142 16
```
</details>

---

