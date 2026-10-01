---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-01 07:23:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 669 |
| Sample Rate | 11.15/sec |
| Health Score | 697% |
| Threads | 8 |
| Allocations | 316 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 11 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 31-43 cores)</summary>

```
1790853571 31
1790853576 31
1790853581 31
1790853586 31
1790853591 31
1790853596 31
1790853601 31
1790853606 31
1790853611 31
1790853616 31
1790853621 31
1790853626 31
1790853631 31
1790853636 31
1790853641 43
1790853646 43
1790853651 43
1790853656 43
1790853661 43
1790853666 43
```
</details>

---

