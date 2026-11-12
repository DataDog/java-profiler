---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 10:57:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 7 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 11 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (4 unique values: 43-47 cores)</summary>

```
1794498709 46
1794498714 46
1794498719 46
1794498724 46
1794498729 46
1794498734 46
1794498739 46
1794498744 46
1794498749 45
1794498754 45
1794498759 45
1794498764 45
1794498769 45
1794498774 45
1794498779 45
1794498784 45
1794498789 45
1794498794 45
1794498799 47
1794498804 47
```
</details>

---

