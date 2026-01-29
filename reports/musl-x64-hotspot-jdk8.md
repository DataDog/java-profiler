---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-01-29 11:12:25 EST

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 159 |
| Sample Rate | 5.30/sec |
| Health Score | 331% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 155 |
| Sample Rate | 5.17/sec |
| Health Score | 323% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 86-96 cores)</summary>

```
1769702689 92
1769702694 86
1769702699 86
1769702704 88
1769702709 88
1769702714 88
1769702719 87
1769702724 87
1769702729 87
1769702734 87
1769702739 87
1769702744 87
1769702749 91
1769702754 91
1769702759 91
1769702764 91
1769702769 91
1769702774 91
1769702779 91
1769702784 91
```
</details>

---

