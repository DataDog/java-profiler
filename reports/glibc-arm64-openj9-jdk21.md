---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 14:50:18 EST

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 829 |
| Sample Rate | 13.82/sec |
| Health Score | 864% |
| Threads | 12 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (2 unique values: 39-59 cores)</summary>

```
1795031186 39
1795031191 39
1795031196 39
1795031201 39
1795031206 39
1795031211 39
1795031216 39
1795031221 39
1795031226 39
1795031231 39
1795031236 39
1795031241 59
1795031246 59
1795031251 59
1795031256 59
1795031261 59
1795031266 59
1795031271 59
1795031276 59
1795031281 59
```
</details>

---

