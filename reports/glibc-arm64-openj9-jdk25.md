---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 11:05:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 11 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 11 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1795449561 43
1795449566 43
1795449571 43
1795449576 43
1795449581 43
1795449586 43
1795449591 43
1795449596 38
1795449601 38
1795449606 38
1795449611 38
1795449616 38
1795449621 38
1795449626 38
1795449631 38
1795449636 38
1795449641 38
1795449646 38
1795449651 38
1795449656 38
```
</details>

---

