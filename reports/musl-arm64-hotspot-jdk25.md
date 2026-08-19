---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-19 04:26:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
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
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 9 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 254 |
| Sample Rate | 4.23/sec |
| Health Score | 264% |
| Threads | 14 |
| Allocations | 142 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1787127694 46
1787127699 46
1787127704 48
1787127709 48
1787127714 43
1787127719 43
1787127724 43
1787127729 43
1787127734 43
1787127739 43
1787127744 43
1787127749 43
1787127754 43
1787127759 43
1787127764 43
1787127769 43
1787127774 43
1787127779 43
1787127784 43
1787127789 43
```
</details>

---

