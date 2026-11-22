---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-22 15:55:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 9 |
| Allocations | 414 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (3 unique values: 17-29 cores)</summary>

```
1795380694 22
1795380699 22
1795380704 22
1795380709 22
1795380714 22
1795380719 22
1795380724 22
1795380729 17
1795380734 17
1795380739 17
1795380744 17
1795380749 17
1795380754 17
1795380759 17
1795380764 17
1795380769 29
1795380774 29
1795380779 29
1795380784 29
1795380789 29
```
</details>

---

