---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 06:17:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 10 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 10 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (2 unique values: 48-64 cores)</summary>

```
1795605123 48
1795605128 48
1795605133 48
1795605138 48
1795605143 48
1795605148 48
1795605153 48
1795605158 48
1795605163 48
1795605168 48
1795605173 48
1795605178 48
1795605183 48
1795605188 48
1795605193 48
1795605198 48
1795605203 48
1795605208 48
1795605213 48
1795605218 48
```
</details>

---

