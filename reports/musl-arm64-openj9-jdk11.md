---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 10:58:04 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 11 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (4 unique values: 30-51 cores)</summary>

```
1794930708 30
1794930713 31
1794930718 31
1794930723 31
1794930728 31
1794930733 31
1794930738 31
1794930743 31
1794930748 31
1794930753 31
1794930758 31
1794930763 31
1794930768 31
1794930773 51
1794930778 51
1794930783 51
1794930788 38
1794930793 38
1794930798 38
1794930803 38
```
</details>

---

