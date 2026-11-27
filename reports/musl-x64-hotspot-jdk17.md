---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-27 08:43:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 8 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (4 unique values: 69-86 cores)</summary>

```
1795786679 69
1795786684 69
1795786689 69
1795786694 69
1795786699 69
1795786704 72
1795786709 72
1795786714 77
1795786719 77
1795786724 77
1795786729 77
1795786734 77
1795786739 77
1795786744 77
1795786749 77
1795786754 77
1795786759 77
1795786764 77
1795786769 77
1795786774 86
```
</details>

---

