---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 05:43:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 10 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (3 unique values: 52-72 cores)</summary>

```
1794998148 72
1794998153 52
1794998158 52
1794998163 52
1794998168 52
1794998173 52
1794998178 52
1794998183 61
1794998188 61
1794998193 61
1794998198 61
1794998203 61
1794998208 61
1794998213 61
1794998218 61
1794998223 61
1794998228 61
1794998233 61
1794998238 61
1794998243 61
```
</details>

---

