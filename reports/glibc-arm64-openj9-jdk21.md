---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-28 12:04:38 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793203199 48
1793203204 48
1793203209 48
1793203214 48
1793203219 48
1793203224 48
1793203229 48
1793203234 48
1793203239 48
1793203244 48
1793203249 48
1793203254 48
1793203259 48
1793203264 48
1793203269 48
1793203274 48
1793203279 48
1793203284 48
1793203289 43
1793203294 43
```
</details>

---

