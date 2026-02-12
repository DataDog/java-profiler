---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-12 13:12:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 779 |
| Sample Rate | 12.98/sec |
| Health Score | 811% |
| Threads | 10 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (2 unique values: 24-29 cores)</summary>

```
1770919627 24
1770919632 24
1770919637 24
1770919642 24
1770919647 29
1770919652 29
1770919657 29
1770919662 29
1770919667 29
1770919672 29
1770919677 29
1770919682 29
1770919687 29
1770919692 29
1770919697 29
1770919702 29
1770919707 29
1770919712 29
1770919717 29
1770919722 29
```
</details>

---

