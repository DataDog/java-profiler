---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 07:19:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 131 |
| Sample Rate | 2.18/sec |
| Health Score | 136% |
| Threads | 8 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 241 |
| Sample Rate | 4.02/sec |
| Health Score | 251% |
| Threads | 14 |
| Allocations | 112 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1795004138 51
1795004143 51
1795004148 51
1795004153 51
1795004158 51
1795004163 51
1795004168 51
1795004173 46
1795004178 46
1795004183 46
1795004188 46
1795004193 46
1795004198 46
1795004203 46
1795004208 46
1795004213 46
1795004218 46
1795004223 46
1795004228 46
1795004233 46
```
</details>

---

