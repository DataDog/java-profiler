---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 10:44:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 809 |
| Sample Rate | 13.48/sec |
| Health Score | 842% |
| Threads | 10 |
| Allocations | 542 |

<details>
<summary>CPU Timeline (2 unique values: 66-72 cores)</summary>

```
1790779115 66
1790779120 66
1790779125 66
1790779130 72
1790779135 72
1790779140 72
1790779145 72
1790779150 72
1790779155 72
1790779160 72
1790779165 72
1790779170 72
1790779175 72
1790779180 72
1790779185 72
1790779190 72
1790779195 72
1790779200 72
1790779205 72
1790779210 72
```
</details>

---

