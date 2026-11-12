---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 11:49:18 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 785 |
| Sample Rate | 13.08/sec |
| Health Score | 817% |
| Threads | 10 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (3 unique values: 22-30 cores)</summary>

```
1794501694 30
1794501699 30
1794501704 30
1794501709 30
1794501714 30
1794501719 30
1794501724 22
1794501729 22
1794501734 22
1794501739 22
1794501744 22
1794501749 22
1794501754 22
1794501759 22
1794501764 22
1794501769 22
1794501774 22
1794501779 22
1794501784 22
1794501789 22
```
</details>

---

