---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 11:31:12 EST

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 8 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 13 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (6 unique values: 37-58 cores)</summary>

```
1795105555 58
1795105561 58
1795105566 51
1795105571 51
1795105576 51
1795105581 51
1795105586 54
1795105591 54
1795105596 54
1795105601 54
1795105606 54
1795105611 54
1795105616 40
1795105621 40
1795105626 37
1795105631 37
1795105636 37
1795105641 37
1795105646 37
1795105651 37
```
</details>

---

