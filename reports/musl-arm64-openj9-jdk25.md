---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-08 12:50:59 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 10 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1775666703 64
1775666708 64
1775666713 64
1775666718 64
1775666723 64
1775666728 64
1775666733 64
1775666738 64
1775666743 64
1775666748 64
1775666753 64
1775666758 64
1775666763 64
1775666768 64
1775666773 64
1775666778 64
1775666783 64
1775666788 64
1775666793 64
1775666798 64
```
</details>

---

