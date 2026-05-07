---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-07 17:29:38 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 10 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 9 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778189116 64
1778189121 64
1778189126 64
1778189131 64
1778189136 64
1778189141 64
1778189146 64
1778189151 64
1778189156 64
1778189161 64
1778189166 64
1778189171 64
1778189176 64
1778189181 64
1778189186 64
1778189191 64
1778189196 64
1778189201 64
1778189206 64
1778189211 64
```
</details>

---

