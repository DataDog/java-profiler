---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 10:44:37 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 912 |
| Sample Rate | 15.20/sec |
| Health Score | 950% |
| Threads | 10 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1790087759 32
1790087764 32
1790087769 32
1790087774 32
1790087779 32
1790087784 32
1790087789 32
1790087794 32
1790087799 32
1790087804 32
1790087809 32
1790087814 32
1790087819 32
1790087824 32
1790087829 32
1790087834 32
1790087839 32
1790087844 32
1790087850 32
1790087855 32
```
</details>

---

