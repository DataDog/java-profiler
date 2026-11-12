---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 10:57:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 921 |
| Sample Rate | 15.35/sec |
| Health Score | 959% |
| Threads | 9 |
| Allocations | 564 |

<details>
<summary>CPU Timeline (4 unique values: 84-87 cores)</summary>

```
1794498704 87
1794498709 85
1794498714 85
1794498719 85
1794498724 85
1794498729 85
1794498734 84
1794498739 84
1794498744 84
1794498749 86
1794498754 86
1794498759 86
1794498764 86
1794498769 86
1794498774 86
1794498779 86
1794498784 86
1794498789 86
1794498794 86
1794498799 86
```
</details>

---

