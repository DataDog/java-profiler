---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-10 08:31:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 12 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (4 unique values: 29-35 cores)</summary>

```
1786364678 29
1786364683 32
1786364688 32
1786364693 32
1786364698 32
1786364703 32
1786364708 32
1786364713 32
1786364718 32
1786364723 35
1786364728 35
1786364733 35
1786364738 35
1786364743 35
1786364748 35
1786364753 35
1786364758 35
1786364763 34
1786364768 34
1786364773 34
```
</details>

---

