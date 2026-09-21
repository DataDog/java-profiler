---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-21 17:43:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 195 |
| Sample Rate | 3.25/sec |
| Health Score | 203% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 62-72 cores)</summary>

```
1790026684 62
1790026689 62
1790026694 62
1790026699 62
1790026704 62
1790026709 62
1790026714 62
1790026719 72
1790026724 72
1790026729 72
1790026734 72
1790026739 72
1790026744 72
1790026749 72
1790026754 72
1790026759 72
1790026764 72
1790026769 72
1790026774 72
1790026779 72
```
</details>

---

