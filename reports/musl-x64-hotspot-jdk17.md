---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 06:08:52 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 792 |
| Sample Rate | 13.20/sec |
| Health Score | 825% |
| Threads | 11 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (2 unique values: 57-64 cores)</summary>

```
1794999729 64
1794999734 64
1794999739 64
1794999744 64
1794999749 64
1794999754 64
1794999759 64
1794999764 64
1794999769 64
1794999774 64
1794999779 64
1794999784 64
1794999789 64
1794999794 64
1794999799 64
1794999804 64
1794999809 64
1794999814 64
1794999819 64
1794999824 64
```
</details>

---

