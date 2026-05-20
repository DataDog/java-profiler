---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-20 05:49:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 12 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (2 unique values: 54-59 cores)</summary>

```
1779270366 59
1779270371 59
1779270376 59
1779270381 59
1779270386 59
1779270391 59
1779270396 54
1779270401 54
1779270406 54
1779270411 54
1779270416 54
1779270421 54
1779270426 54
1779270431 54
1779270436 54
1779270441 54
1779270446 54
1779270451 54
1779270456 54
1779270461 54
```
</details>

---

